#include "QColorListView.h"

class QColorListViewPrivate : public QObject {
    Q_OBJECT

public:
    explicit QColorListViewPrivate(QColorListView *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , model(new QColorListModel(this)) {
        Q_ASSERT(widget);

        widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        widget->setModel(model);
    }

    QString internalColorName(const QColor &color) const {
        return color.name(QColor::HexArgb);
    }

public:
    QColorListView *widget;
    QColorListModel *model;
};

QColorListView::QColorListView(QWidget *parent)
    : QListView(parent)
    , d(new QColorListViewPrivate(this)) {
}

QColorListView::QColorListView(const QStringList &colorListNames, QWidget *parent)
    : QListView(parent)
    , d(new QColorListViewPrivate(this)) {
    d->model->setColorListNames(colorListNames);
}

QColorListView::QColorListView(const QList<QColor> &colors, QWidget *parent)
    : QListView(parent)
    , d(new QColorListViewPrivate(this)) {
    d->model->setColorsList(colors);
}

QColorListModel::NameFormat QColorListView::nameFormat() const {
    return d->model->nameFormat();
}

void QColorListView::setNameFormat(QColorListModel::NameFormat nameFormat) {
    d->model->setNameFormat(nameFormat);
}

QStringList QColorListView::colorListNames() const {
    return d->model->colorListNames();
}

void QColorListView::setColorListNames(const QStringList &colorNames) {
    d->model->setColorListNames(colorNames);
}

QList<QColor> QColorListView::colorsList() const {
    return d->model->colorsList();
}

void QColorListView::setColorsList(const QList<QColor> &colors) {
    d->model->setColorsList(colors);
}

QStringList QColorListView::selectedColorListNames() const {
    const QModelIndexList indexes = selectionModel()->selectedRows();
    QStringList colors;

    foreach (const QModelIndex &index, indexes) {
        colors << index.data(static_cast<int>(QColorListModel::Role::HexArgbName)).toString();
    }

    return colors;
}

void QColorListView::setSelectedColorListNames(const QStringList &colorListNames) {
    QSet<QString> colors;
    QItemSelection selection;

    foreach (const QString &colorName, colorListNames) {
        colors << d->internalColorName(QColor(colorName));
    }

    for (int i = 0; i < d->model->rowCount(); i++) {
        const QModelIndex index = d->model->index(i, 0);
        const QString colorName = index.data(static_cast<int>(QColorListModel::Role::HexArgbName)).toString();

        if (colors.contains(colorName)) {
            selection.select(index, index);
        }
    }

    selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
}

QList<QColor> QColorListView::selectedColorsList() const {
    const QModelIndexList indexes = selectionModel()->selectedRows();
    QList<QColor> colors;

    foreach (const QModelIndex &index, indexes) {
        colors << QColor(index.data(static_cast<int>(QColorListModel::Role::HexArgbName)).toString());
    }

    return colors;
}

void QColorListView::setSelectedColorsList(const QList<QColor> &colorsList) {
    QSet<QString> colors;
    QItemSelection selection;

    foreach (const QColor &color, colorsList) {
        colors << d->internalColorName(color);
    }

    for (int i = 0; i < d->model->rowCount(); i++) {
        const QModelIndex index = d->model->index(i, 0);
        const QString colorName = index.data(static_cast<int>(QColorListModel::Role::HexArgbName)).toString();

        if (colors.contains(colorName)) {
            selection.select(index, index);
        }
    }

    selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
}

#include "QColorListView.moc"
