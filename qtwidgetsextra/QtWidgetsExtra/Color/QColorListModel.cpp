#include "QColorListModel.h"
#include "QtWidgetsExtra/QtWidgetsExtraCache.h"

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
    QStringList colors;
};

static bool ascendingLessThan(const QPair<QString, int> &s1, const QPair<QString, int> &s2)
{
    return s1.first < s2.first;
}

static bool decendingLessThan(const QPair<QString, int> &s1, const QPair<QString, int> &s2)
{
    return s1.first > s2.first;
}

QColorListModel::QColorListModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new QColorListModelPrivate(this))
{
}

QColorListModel::QColorListModel(const QStringList &colorListNames, QObject *parent)
    : QAbstractListModel(parent)
    , d(new QColorListModelPrivate(this))
{
    d->colors = colorListNames;
}

QColorListModel::QColorListModel(const QList<QColor> &colorsList, QObject *parent)
    : QAbstractListModel(parent)
    , d(new QColorListModelPrivate(this))
{
    QStringList colors;

    foreach (const QColor &color, colorsList) {
        colors << color.name(QColor::HexArgb);
    }

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

    if (role == Qt::DecorationRole) {
        return QtWidgetsExtraCache::cachedIconColor(QColor(d->colors.at(index.row())), QSize(64, 64));
    }
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return QColor(d->colors.at(index.row())).name(QColor::NameFormat(d->nameFormat));
    }
    else if (role == QColorListModel::HexArgbName) {
        return d->colors.at(index.row());
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
        d->colors.replace(index.row(), value.value<QColor>().name(QColor::HexArgb));
        Q_EMIT dataChanged(index, index, QVector<int>() << role);
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
        d->colors.insert(row, QString());
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
    Q_EMIT layoutAboutToBeChanged(QList<QPersistentModelIndex>(), VerticalSortHint);

    QList<QPair<QString, int> > list;
    for (int i = 0; i < d->colors.count(); ++i) {
        list.append(QPair<QString, int>(d->colors.at(i), i));
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

    Q_EMIT layoutChanged(QList<QPersistentModelIndex>(), VerticalSortHint);
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
        Q_EMIT dataChanged(index(0,0), index(rowCount() -1, 0), QVector<int>() << Qt::DisplayRole);
    }
}

QStringList QColorListModel::colorListNames() const
{
    return d->colors;
}

void QColorListModel::setColorListNames(const QStringList &colorListNames)
{
    QStringList colors;

    foreach (const QString &colorName, colorListNames) {
        colors << QColor(colorName).name(QColor::HexArgb);
    }

    Q_EMIT beginResetModel();
    d->colors = colors;
    Q_EMIT endResetModel();
}

QList<QColor> QColorListModel::colorsList() const
{
    QList<QColor> colors;

    foreach (const QString &colorName, d->colors) {
        colors << QColor(colorName);
    }

    return colors;
}

void QColorListModel::setColorsList(const QList<QColor> &colorsList)
{
    QStringList colors;

    foreach (const QColor &color, colorsList) {
        colors << color.name(QColor::HexArgb);
    }

    Q_EMIT beginResetModel();
    d->colors = colors;
    Q_EMIT endResetModel();
}

#include "QColorListModel.moc"
