#include "QFileSystemListView.h"

#include <QApplication>
#include <QFileSystemModel>

class QFileSystemListViewPrivate : public QObject {
    Q_OBJECT

public:
    QFileSystemListViewPrivate(QFileSystemListView *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , model(new QFileSystemModel(this))
        , browsable(!(model->filter() & QDir::NoDotDot)) {
        Q_ASSERT(widget);

        connect(model, &QFileSystemModel::directoryLoaded, widget, &QFileSystemListView::directoryLoaded);
        connect(model, &QFileSystemModel::fileRenamed, widget, &QFileSystemListView::fileRenamed);
        connect(model, &QFileSystemModel::rootPathChanged, widget, &QFileSystemListView::rootPathChanged);
        connect(widget, &QFileSystemListView::activated, this, &QFileSystemListViewPrivate::activated);
    }

    void updateItemSelection(const QStringList &selection, QItemSelectionModel::SelectionFlags flags,
                             int column = 0) const {
        // QMap give us sorting for free
        QMap<QModelIndex, QMap<QModelIndex, int>> mapIndexes;
        QItemSelection itemSelection;

        foreach (const QString &item, selection) {
            const QModelIndex index = model->index(item, column);

            if (index.isValid()) {
                mapIndexes[index.parent()][index]++;
            }
        }

        foreach (const QModelIndex &parent, mapIndexes.keys()) {
            const QModelIndexList indexes = mapIndexes[parent].keys();
            int top = -1;
            int bottom = -1;

            for (int i = 0; i < indexes.count(); i++) {
                const QModelIndex &index = indexes[i];
                const bool hasNext = i + 1 < indexes.count();

                if (top == -1) {
                    top = index.row();
                } else {
                    if (bottom == -1) {
                        // index is not contiguous
                        if (index.row() != top + 1) {
                            const QModelIndex idx = model->index(top, column, parent);
                            itemSelection << QItemSelectionRange(idx, idx);

                            top = index.row();
                            bottom = -1;
                        } else {
                            bottom = index.row();
                        }
                    } else if (index.row() != bottom + 1) {
                        // index is not contiguous
                        if (index.row() != top + 1) {
                            const QModelIndex idx1 = model->index(top, column, parent);
                            const QModelIndex idx2 = model->index(bottom, column, parent);
                            itemSelection << QItemSelectionRange(idx1, idx2);

                            top = index.row();
                            bottom = -1;
                        } else {
                            bottom = index.row();
                        }
                    }
                }

                if (!hasNext && top != -1) {
                    if (bottom == -1) {
                        bottom = top;
                    }

                    const QModelIndex idx1 = model->index(top, column, parent);
                    const QModelIndex idx2 = model->index(bottom, column, parent);
                    itemSelection << QItemSelection(idx1, idx2);

                    top = -1;
                    bottom = -1;
                }
            }
        }

        widget->selectionModel()->select(itemSelection, flags);
    }

public Q_SLOTS:
    void activated(const QModelIndex &index) {
        if (!browsable || !model->isDir(index) || QApplication::keyboardModifiers() != Qt::NoModifier) {
            return;
        }

        const QFileInfo fileInfo = model->fileInfo(index);
        if (fileInfo.isReadable()) {
            widget->setRootPath(fileInfo.filePath());

            if (fileInfo.isRoot() || !browsable) {
                model->setFilter(model->filter() | QDir::NoDotDot);
            } else {
                model->setFilter(model->filter() & ~QDir::NoDotDot);
            }
        }
    }

public:
    QFileSystemListView *widget;
    QFileSystemModel *model;
    bool browsable;
};

QFileSystemListView::QFileSystemListView(QWidget *parent)
    : QListView(parent)
    , d(new QFileSystemListViewPrivate(this)) {
    setUniformItemSizes(true);
    QListView::setModel(d->model);
    setRootPath(QDir::homePath());
}

void QFileSystemListView::setModel(QAbstractItemModel *model) {
    Q_UNUSED(model);
}

bool QFileSystemListView::nameFilterDisables() const {
    return d->model->nameFilterDisables();
}

void QFileSystemListView::setNameFilterDisables(bool nameFilterDisables) {
    d->model->setNameFilterDisables(nameFilterDisables);
}

bool QFileSystemListView::readOnly() const {
    return d->model->isReadOnly();
}

void QFileSystemListView::setReadOnly(bool readOnly) {
    d->model->setReadOnly(readOnly);
}

bool QFileSystemListView::resolveSymlinks() const {
    return d->model->resolveSymlinks();
}

void QFileSystemListView::setResolveSymlinks(bool resolveSymlinks) {
    d->model->setResolveSymlinks(resolveSymlinks);
}

bool QFileSystemListView::browsable() const {
    return d->browsable;
}

void QFileSystemListView::setBrowsable(bool browsable) {
    if (d->browsable == browsable) {
        return;
    }

    d->browsable = browsable;

    if (d->model->rootDirectory().isRoot() || !d->browsable) {
        d->model->setFilter(d->model->filter() | QDir::NoDotDot);
    } else {
        d->model->setFilter(d->model->filter() & ~QDir::NoDotDot);
    }
}

QDir::Filters QFileSystemListView::filters() const {
    return d->model->filter();
}

void QFileSystemListView::setFilters(QDir::Filters filters) {
    d->model->setFilter(filters);
}

QStringList QFileSystemListView::nameFilters() const {
    return d->model->nameFilters();
}

void QFileSystemListView::setNameFilters(const QStringList &nameFilters) {
    d->model->setNameFilters(nameFilters);
}

QFileSystemListView::SectionFlag QFileSystemListView::visibleSection() const {
    switch (modelColumn()) {
    case QFileSystemListView::NameColumn:
        return QFileSystemListView::NameSection;
    case QFileSystemListView::SizeColumn:
        return QFileSystemListView::SizeSection;
    case QFileSystemListView::TypeColumn:
        return QFileSystemListView::TypeSection;
    case QFileSystemListView::LastModificationColumn:
        return QFileSystemListView::LastModificationSection;
    default:
        return QFileSystemListView::NameSection;
    }
}

void QFileSystemListView::setVisibleSection(QFileSystemListView::SectionFlag section) {
    switch (section) {
    case QFileSystemListView::NameSection:
        setModelColumn(QFileSystemListView::NameColumn);
        break;
    case QFileSystemListView::SizeSection:
        setModelColumn(QFileSystemListView::SizeColumn);
        break;
    case QFileSystemListView::TypeSection:
        setModelColumn(QFileSystemListView::TypeColumn);
        break;
    case QFileSystemListView::LastModificationSection:
        setModelColumn(QFileSystemListView::LastModificationColumn);
        break;
    default:
        setModelColumn(QFileSystemListView::NameColumn);
        break;
    }
}

QString QFileSystemListView::rootPath() const {
    return d->model->rootPath();
}

void QFileSystemListView::setRootPath(const QString &rootPath) {
    d->model->setRootPath(rootPath);
    setRootIndex(d->model->index(rootPath));
}

QStringList QFileSystemListView::selection() const {
    const QModelIndexList indexes = selectionModel()->selectedRows(modelColumn());
    QStringList selection;

    foreach (const QModelIndex &index, indexes) {
        selection << d->model->fileInfo(index).absoluteFilePath();
    }

    return selection;
}

void QFileSystemListView::setSelection(const QStringList &selection) {
    d->updateItemSelection(selection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows, modelColumn());
}

void QFileSystemListView::addSelection(QStringList &selection) {
    d->updateItemSelection(selection, QItemSelectionModel::Select | QItemSelectionModel::Rows, modelColumn());
}

void QFileSystemListView::clearSelection() {
    selectionModel()->clearSelection();
}

#include "QFileSystemListView.moc"
