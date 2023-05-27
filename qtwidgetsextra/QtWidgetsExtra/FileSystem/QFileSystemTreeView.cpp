#include "QFileSystemTreeView.h"

#include <QFileSystemModel>
#include <QHeaderView>

class QFileSystemTreeViewPrivate : public QObject {
    Q_OBJECT

public:
    explicit QFileSystemTreeViewPrivate(QFileSystemTreeView *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , model(new QFileSystemModel(this)) {
        connect(model, &QFileSystemModel::directoryLoaded, widget, &QFileSystemTreeView::directoryLoaded);
        connect(model, &QFileSystemModel::fileRenamed, widget, &QFileSystemTreeView::fileRenamed);
        connect(model, &QFileSystemModel::rootPathChanged, widget, &QFileSystemTreeView::rootPathChanged);
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

public:
    QFileSystemTreeView *widget;
    QFileSystemModel *model;
};

QFileSystemTreeView::QFileSystemTreeView(QWidget *parent)
    : QTreeView(parent)
    , d(new QFileSystemTreeViewPrivate(this)) {
    setUniformRowHeights(true);
    QTreeView::setModel(d->model);
    setRootPath(QDir::homePath());
    header()->setStretchLastSection(false);
    header()->setSectionResizeMode(static_cast<int>(QFileSystemTreeView::Column::Name), QHeaderView::Stretch);
}

void QFileSystemTreeView::setModel(QAbstractItemModel *model) {
    Q_UNUSED(model);
}

bool QFileSystemTreeView::nameFilterDisables() const {
    return d->model->nameFilterDisables();
}

void QFileSystemTreeView::setNameFilterDisables(bool nameFilterDisables) {
    d->model->setNameFilterDisables(nameFilterDisables);
}

bool QFileSystemTreeView::readOnly() const {
    return d->model->isReadOnly();
}

void QFileSystemTreeView::setReadOnly(bool readOnly) {
    d->model->setReadOnly(readOnly);
}

bool QFileSystemTreeView::resolveSymlinks() const {
    return d->model->resolveSymlinks();
}

void QFileSystemTreeView::setResolveSymlinks(bool resolveSymlinks) {
    d->model->setResolveSymlinks(resolveSymlinks);
}

QDir::Filters QFileSystemTreeView::filters() const {
    return d->model->filter();
}

void QFileSystemTreeView::setFilters(QDir::Filters filters) {
    d->model->setFilter(filters);
}

QStringList QFileSystemTreeView::nameFilters() const {
    return d->model->nameFilters();
}

void QFileSystemTreeView::setNameFilters(const QStringList &nameFilters) {
    d->model->setNameFilters(nameFilters);
}

QFileSystemTreeView::Sections QFileSystemTreeView::visibleSections() const {
    const auto isSectionHidden = [this](QFileSystemTreeView::Column column) {
        return header()->isSectionHidden(static_cast<int>(column));
    };
    QFileSystemTreeView::Sections sections = QFileSystemTreeView::Section::All;

    if (header()->hiddenSectionCount() > 0) {
        if (!isSectionHidden(QFileSystemTreeView::Column::Name)) {
            sections |= QFileSystemTreeView::Section::Name;
        }

        if (!isSectionHidden(QFileSystemTreeView::Column::Size)) {
            sections |= QFileSystemTreeView::Section::Size;
        }

        if (!isSectionHidden(QFileSystemTreeView::Column::Type)) {
            sections |= QFileSystemTreeView::Section::Type;
        }

        if (!isSectionHidden(QFileSystemTreeView::Column::LastModification)) {
            sections |= QFileSystemTreeView::Section::LastModification;
        }
    }

    return sections;
}

void QFileSystemTreeView::setVisibleSections(QFileSystemTreeView::Sections sections) {
    const auto isSectionHidden = [this](QFileSystemTreeView::Column column) {
        return header()->isSectionHidden(static_cast<int>(column));
    };
    const auto setSectionHidden = [this](QFileSystemTreeView::Column column, bool hidden) {
        header()->setSectionHidden(static_cast<int>(column), hidden);
    };
    const auto resizeSection = [this](QFileSystemTreeView::Column column, int size) {
        header()->resizeSection(static_cast<int>(column), size);
    };

    if (sections == Sections(QFileSystemTreeView::Section::All)) {
        setSectionHidden(QFileSystemTreeView::Column::Name, false);
        setSectionHidden(QFileSystemTreeView::Column::Size, false);
        setSectionHidden(QFileSystemTreeView::Column::Type, false);
        setSectionHidden(QFileSystemTreeView::Column::LastModification, false);
    } else {
        setSectionHidden(QFileSystemTreeView::Column::Name, !sections.testFlag(QFileSystemTreeView::Section::Name));
        setSectionHidden(QFileSystemTreeView::Column::Size, !sections.testFlag(QFileSystemTreeView::Section::Size));
        setSectionHidden(QFileSystemTreeView::Column::Type, !sections.testFlag(QFileSystemTreeView::Section::Type));
        setSectionHidden(QFileSystemTreeView::Column::LastModification,
                         !sections.testFlag(QFileSystemTreeView::Section::LastModification));
    }

    header()->setStretchLastSection(isSectionHidden(QFileSystemTreeView::Column::Name));
    resizeSection(QFileSystemTreeView::Column::Name, header()->defaultSectionSize());
    resizeSection(QFileSystemTreeView::Column::Size, header()->defaultSectionSize());
    resizeSection(QFileSystemTreeView::Column::Type, header()->defaultSectionSize());
    resizeSection(QFileSystemTreeView::Column::LastModification, header()->defaultSectionSize());
}

QString QFileSystemTreeView::rootPath() const {
    return d->model->rootPath();
}

void QFileSystemTreeView::setRootPath(const QString &rootPath) {
    d->model->setRootPath(rootPath);
    setRootIndex(d->model->index(rootPath));
}

QStringList QFileSystemTreeView::selection() const {
    const QModelIndexList indexes = selectionModel()->selectedRows();
    QStringList selection;

    foreach (const QModelIndex &index, indexes) {
        selection << d->model->fileInfo(index).absoluteFilePath();
    }

    return selection;
}

void QFileSystemTreeView::setSelection(const QStringList &selection) {
    d->updateItemSelection(selection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
}

void QFileSystemTreeView::addSelection(QStringList &selection) {
    d->updateItemSelection(selection, QItemSelectionModel::Select | QItemSelectionModel::Rows);
}

void QFileSystemTreeView::clearSelection() {
    selectionModel()->clearSelection();
}

#include "QFileSystemTreeView.moc"
