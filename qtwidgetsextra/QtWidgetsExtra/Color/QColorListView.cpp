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

QStringList QColorListView::colorNames() const {
    return d->model->colorListNames();
}

void QColorListView::setColorNames(const QStringList &colorNames) {
    d->model->setColorListNames(colorNames);
}

QList<QColor> QColorListView::colors() const {
    return d->model->colorsList();
}

void QColorListView::setColors(const QList<QColor> &colors) {
    d->model->setColorsList(colors);
}

QStringList QColorListView::selectedColorNames() const {
    const QModelIndexList indexes = selectionModel()->selectedRows();
    QStringList colors;

    foreach (const QModelIndex &index, indexes) {
        colors << index.data(static_cast<int>(QColorListModel::Role::HexArgbName)).toString();
    }

    return colors;
}

void QColorListView::setSelectedColorNames(const QStringList &colorListNames) {
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

QList<QColor> QColorListView::selectedColors() const {
    const QModelIndexList indexes = selectionModel()->selectedRows();
    QList<QColor> colors;

    foreach (const QModelIndex &index, indexes) {
        colors << QColor(index.data(static_cast<int>(QColorListModel::Role::HexArgbName)).toString());
    }

    return colors;
}

void QColorListView::setSelectedColors(const QList<QColor> &colorsList) {
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
