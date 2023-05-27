#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QAbstractItemModel>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QAbstractButtonListModel : public QAbstractListModel {
    Q_OBJECT
    class QAbstractButtonListModelPrivate *d;

public:
    enum class Role {
        Id = Qt::UserRole,
        Shortcut
    };
    Q_ENUM(Role)

    explicit QAbstractButtonListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void clear();
};
