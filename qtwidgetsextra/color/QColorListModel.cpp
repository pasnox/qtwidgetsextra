#include "QColorListModel.h"
#include "QtWidgetsExtraCache.h"

#include <QVector>
#include <QIcon>

#include <algorithm>

class QColorListModelPrivate : public QObject {
    Q_OBJECT

public:
    QColorListModelPrivate(QColorListModel *objectP)
        : QObject(objectP)
        , object(objectP)
        , nameFormat(QColorListModel::HexRgb) {
        Q_ASSERT(object);
    }

public:
    QColorListModel *object;
    QColorListModel::NameFormat nameFormat;
    QList<QColor> colors;
};

static bool ascendingLessThan(const QPair<QColor, int> &s1, const QPair<QColor, int> &s2)
{
    return s1.first.name(QColor::HexArgb) < s2.first.name(QColor::HexArgb);
}

static bool decendingLessThan(const QPair<QColor, int> &s1, const QPair<QColor, int> &s2)
{
    return s1.first.name(QColor::HexArgb) > s2.first.name(QColor::HexArgb);
}

QColorListModel::QColorListModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new QColorListModelPrivate(this))
{
}

QColorListModel::QColorListModel(const QList<QColor> &colors, QObject *parent)
    : QAbstractListModel(parent)
    , d(new QColorListModelPrivate(this))
{
    d->colors = colors;
}

int QColorListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return d->colors.count();
}

QModelIndex QColorListModel::sibling(int row, int column, const QModelIndex &idx) const
{
    if (!idx.isValid() || column != 0 || row >= d->colors.count()) {
        return QModelIndex();
    }

    return createIndex(row, 0);
}

QVariant QColorListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= d->colors.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return d->colors.at(index.row()).name(QColor::NameFormat(d->nameFormat));
    }
    else if (role == Qt::DecorationRole) {
        return QtWidgetsExtraCache::cachedIconColor(d->colors.at(index.row()), QSize(64, 64));
    }

    return QVariant();
}

Qt::ItemFlags QColorListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QAbstractListModel::flags(index) | Qt::ItemIsDropEnabled;
    }

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool QColorListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < d->colors.size()
        && (role == Qt::EditRole || role == Qt::DisplayRole)) {
        d->colors.replace(index.row(), value.value<QColor>());
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }

    return false;
}

bool QColorListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent)) {
        return false;
    }

    beginInsertRows(QModelIndex(), row, row +count -1);

    for (int r = 0; r < count; ++r) {
        d->colors.insert(row, QColor());
    }

    endInsertRows();

    return true;
}

bool QColorListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row +count) > rowCount(parent)) {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row +count -1);

    for (int r = 0; r < count; ++r) {
        d->colors.removeAt(row);
    }

    endRemoveRows();

    return true;
}

void QColorListModel::sort(int, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged(QList<QPersistentModelIndex>(), VerticalSortHint);

    QList<QPair<QColor, int> > list;
    for (int i = 0; i < d->colors.count(); ++i) {
        list.append(QPair<QColor, int>(d->colors.at(i), i));
    }

    if (order == Qt::AscendingOrder) {
        std::sort(list.begin(), list.end(), ascendingLessThan);
    }
    else {
        std::sort(list.begin(), list.end(), decendingLessThan);
    }

    d->colors.clear();
    QVector<int> forwarding(list.count());
    for (int i = 0; i < list.count(); ++i) {
        d->colors.append(list.at(i).first);
        forwarding[list.at(i).second] = i;
    }

    QModelIndexList oldList = persistentIndexList();
    QModelIndexList newList;
    for (int i = 0; i < oldList.count(); ++i) {
        newList.append(index(forwarding.at(oldList.at(i).row()), 0));
    }
    changePersistentIndexList(oldList, newList);

    emit layoutChanged(QList<QPersistentModelIndex>(), VerticalSortHint);
}

Qt::DropActions QColorListModel::supportedDropActions() const
{
    return QAbstractItemModel::supportedDropActions() | Qt::MoveAction;
}

QColorListModel::NameFormat QColorListModel::nameFormat() const
{
    return d->nameFormat;
}

void QColorListModel::setNameFormat(QColorListModel::NameFormat nameFormat)
{
    d->nameFormat = nameFormat;

    if (rowCount() > 0) {
        emit dataChanged(index(0,0), index(rowCount() -1, 0), QVector<int>() << Qt::DisplayRole);
    }
}

QList<QColor> QColorListModel::colorList() const
{
    return d->colors;
}

void QColorListModel::setColorList(const QList<QColor> &colors)
{
    emit beginResetModel();
    d->colors = colors;
    emit endResetModel();
}

QStringList QColorListModel::colorListNames() const
{
    QStringList colors;

    for (int i = 0; i < rowCount(); i++) {
        colors << data(index(i, 0), Qt::DisplayRole).toString();
    }

    return colors;
}

void QColorListModel::setColorListNames(const QStringList &colorListNames)
{
    QList<QColor> colors;

    foreach (const QString &colorName, colorListNames) {
        colors << QColor(colorName);
    }

    setColorList(colors);
}

#include "QColorListModel.moc"
