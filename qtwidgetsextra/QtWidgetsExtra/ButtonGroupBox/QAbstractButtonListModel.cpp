#include "QAbstractButtonListModel.h"

#include <QVector>

class QAbstractButtonListModelPrivate : public QObject {
    Q_OBJECT

public:
    explicit QAbstractButtonListModelPrivate(QAbstractButtonListModel *model)
        : QObject(model)
        , model(model) {
        Q_ASSERT(model);
    }

public:
    using Button = QMap<int, QVariant>;
    using Buttons = QVector<Button>;

    QAbstractButtonListModel *model;
    Buttons buttons;
};

QAbstractButtonListModel::QAbstractButtonListModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new QAbstractButtonListModelPrivate(this)) {
}

int QAbstractButtonListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }

    return d->buttons.count();
}

QVariant QAbstractButtonListModel::data(const QModelIndex &index, int role) const {
    if (hasIndex(index.row(), index.column(), index.parent())) {
        return d->buttons[index.row()][role];
    }

    return QVariant();
}

Qt::ItemFlags QAbstractButtonListModel::flags(const QModelIndex &index) const {
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemNeverHasChildren;
}

bool QAbstractButtonListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (hasIndex(index.row(), index.column(), index.parent()) && role != Qt::EditRole) {
        QAbstractButtonListModelPrivate::Button &button = d->buttons[index.row()];
        auto it = button.find(role);

        if (it == button.end()) {
            if (value.isNull()) {
                return false;
            }

            button[role] = value;
        } else {
            if (value.isNull()) {
                button.erase(it);
            } else if ((*it) == value) {
                return false;
            } else {
                button[role] = value;
            }
        }

        Q_EMIT dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

bool QAbstractButtonListModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (count < 1 || row < 0 || row > rowCount(parent) || parent.isValid()) {
        return false;
    }

    beginInsertRows(QModelIndex(), row, row + count - 1);
    d->buttons.insert(row, count, {});
    endInsertRows();

    return true;
}

bool QAbstractButtonListModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (count < 1 || row < 0 || (row + count) > rowCount(parent) || parent.isValid()) {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    d->buttons.remove(row, count);
    endRemoveRows();

    return true;
}

void QAbstractButtonListModel::clear() {
    removeRows(0, rowCount(), QModelIndex());
}

#include "QAbstractButtonListModel.moc"
