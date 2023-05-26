#ifndef QABSTRACTBUTTONLISTMODEL_H
#define QABSTRACTBUTTONLISTMODEL_H

#include <QAbstractItemModel>

class QAbstractButtonListModel : public QAbstractListModel
{
    Q_OBJECT
    class QAbstractButtonListModelPrivate *d;

public:
    enum Roles {
        IdRole = Qt::UserRole,
        ShortcutRole
    };

    explicit QAbstractButtonListModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    void clear();
};

#endif // QABSTRACTBUTTONLISTMODEL_H
