#include "QFileSystemComboBox.h"
#include "QFileSystemListView.h"

#include <QFileSystemModel>
#include <QCompleter>

#include <optional>

class QFileSystemComboBoxCompleter : public QCompleter {
public:
    using QCompleter::QCompleter;

    QString pathFromIndex(const QModelIndex &index) const override {
        return index.data(completionRole()).toString();
    }

    QStringList splitPath(const QString &path) const override {
        if (const auto model = qobject_cast<QFileSystemModel *>(QCompleter::model())) {
            return QCompleter::splitPath(QDir(model->rootPath()).filePath(path));
        }

        Q_UNREACHABLE();
    }
};

class QFileSystemComboBoxPrivate : public QObject {
    Q_OBJECT

public:
    using LayoutValue = std::optional<QPair<int, QFileInfo>>;

    explicit QFileSystemComboBoxPrivate(QFileSystemComboBox *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , view(new QFileSystemListView(widget)) {
        Q_ASSERT(widget);

        view->setBrowsable(false);
        view->setReadOnly(true);

        widget->blockSignals(true);
        widget->QComboBox::setEditable(true);
        widget->QComboBox::setModel(view->model());
        widget->QComboBox::setView(view);
        widget->QComboBox::setRootModelIndex(view->rootIndex());
        widget->QComboBox::setCurrentIndex(-1);

        auto completer = new QFileSystemComboBoxCompleter(view->model(), this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionRole(Qt::DisplayRole);
        completer->setFilterMode(Qt::MatchContains);
        completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
        widget->setCompleter(completer);

        // QFileSystemModel sorting is delayed and use layoutChanged.
        // And QComboBox model watching does not listen to layoutChanged...

        connect(widget->QComboBox::model(), &QAbstractItemModel::layoutAboutToBeChanged, widget, [this]() {
            if (!initialSorting && !layoutValue) {
                layoutValue = qMakePair(widget->currentIndex(), QFileInfo(widget->currentFilePath()));
            }
        });
        connect(widget->QComboBox::model(), &QAbstractItemModel::layoutChanged, widget, [this]() {
            if (initialSorting && !layoutValue && widget->QComboBox::model()->rowCount(widget->QComboBox::rootModelIndex()) > 0) {
                layoutValue = qMakePair(0, QFileInfo(widget->filePath(0)));
            }

            initialSorting = false;

            bool done = false;

            if (layoutValue) {
                Q_ASSERT(layoutValue->second.filePath().isEmpty() || view->rootPath() == layoutValue->second.path());

                // If we have both a valid index and file path, both needs to match
                if (layoutValue->first >= 0 && !layoutValue->second.filePath().isEmpty()) {
                    done = true;
                    widget->QComboBox::setCurrentIndex(layoutValue->first);
                } else if (layoutValue->first >= 0) {
                    done = true;
                    widget->QComboBox::setCurrentIndex(layoutValue->first);
                } else if (!layoutValue->second.filePath().isEmpty()) {
                    done = true;
                    widget->QComboBox::setCurrentIndex(widget->findFileName(layoutValue->second.fileName()));
                } else {
                    Q_UNREACHABLE();
                }
            }

            layoutValue.reset();

            if (!done) {
                widget->QComboBox::setCurrentIndex(-1);
            }
        });

        connect(view, &QFileSystemListView::directoryLoaded, this, [this](const QString &path) {
            if (widget->signalsBlocked()) {
                widget->blockSignals(false);
            }

            Q_EMIT widget->directoryLoaded(path);
        });

        connect(view, &QFileSystemListView::rootPathChanged, this, [this](const QString &path) {
            widget->QComboBox::setRootModelIndex(view->rootIndex());
            Q_EMIT widget->rootPathChanged(path);
        });

        connect(widget, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int index) {
            Q_EMIT widget->currentFileNameChanged(widget->fileName(index));
            Q_EMIT widget->currentFilePathChanged(widget->filePath(index));
        });
    }

    void setRootPath(const QString &rootPath, const LayoutValue &lv) {
        initialSorting = true;
        layoutValue = lv;
        view->setRootPath(rootPath);
    }

public:
    QFileSystemComboBox *widget;
    QFileSystemListView *view;
    bool initialSorting = true;
    LayoutValue layoutValue;
};

QFileSystemComboBox::QFileSystemComboBox(QWidget *parent)
    : QComboBox(parent)
    , d(new QFileSystemComboBoxPrivate(this)) {
}

bool QFileSystemComboBox::nameFilterDisables() const {
    return d->view->nameFilterDisables();
}

void QFileSystemComboBox::setNameFilterDisables(bool nameFilterDisables) {
    d->view->setNameFilterDisables(nameFilterDisables);
}

bool QFileSystemComboBox::resolveSymlinks() const {
    return d->view->resolveSymlinks();
}

void QFileSystemComboBox::setResolveSymlinks(bool resolveSymlinks) {
    d->view->setResolveSymlinks(resolveSymlinks);
}

QDir::Filters QFileSystemComboBox::filters() const {
    return d->view->filters();
}

void QFileSystemComboBox::setFilters(QDir::Filters filters) {
    d->view->setFilters(filters);
}

QStringList QFileSystemComboBox::nameFilters() const {
    return d->view->nameFilters();
}

void QFileSystemComboBox::setNameFilters(const QStringList &nameFilters) {
    d->view->setNameFilters(nameFilters);
}

QFileSystemComboBox::Section QFileSystemComboBox::visibleSection() const {
    return static_cast<QFileSystemComboBox::Section>(d->view->visibleSection());
}

void QFileSystemComboBox::setVisibleSection(QFileSystemComboBox::Section section) {
    d->view->setVisibleSection(static_cast<QFileSystemListView::Section>(section));
}

QString QFileSystemComboBox::rootPath() const {
    return d->view->rootPath();
}

void QFileSystemComboBox::setRootPath(const QString &rootPath) {
    d->setRootPath(rootPath, {});
}

QString QFileSystemComboBox::currentFileName() const {
    return QFileInfo(currentFilePath()).fileName();
}

void QFileSystemComboBox::setCurrentFileName(const QString &fileName) {
    setCurrentFilePath(QDir(rootPath()).filePath(fileName));
}

QString QFileSystemComboBox::currentFilePath() const {
    return currentData(QFileSystemModel::FilePathRole).toString();
}

void QFileSystemComboBox::setCurrentFilePath(const QString &filePath) {
    const QFileInfo fileInfo(filePath);

    if (rootPath() != fileInfo.absolutePath()) {
        d->setRootPath(fileInfo.absolutePath(), qMakePair(-1, fileInfo.absoluteFilePath()));
    } else {
        if (d->initialSorting || d->layoutValue) {
            d->layoutValue = qMakePair(-1, fileInfo.absoluteFilePath());
        } else {
            setCurrentIndex(findFileName(fileInfo.fileName()));
        }
    }
}

QString QFileSystemComboBox::fileName(int index) const {
    return itemData(index, QFileSystemModel::FileNameRole).toString();
}

QString QFileSystemComboBox::filePath(int index) const {
    return itemData(index, QFileSystemModel::FilePathRole).toString();
}

int QFileSystemComboBox::findFileName(const QString &fileName, Qt::MatchFlags flags) const {
    return findData(fileName, QFileSystemModel::FileNameRole, flags);
}

#include "QFileSystemComboBox.moc"
