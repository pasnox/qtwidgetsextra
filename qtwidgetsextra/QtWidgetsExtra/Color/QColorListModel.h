#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QAbstractItemModel>
#include <QColor>
#include <QStringList>

// NOTE: This class duplicate QColor::NameFormat because this is not a Qt namespace available enum for Qt Designer.

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QColorListModel : public QAbstractListModel {
    Q_OBJECT
    class QColorListModelPrivate *d;

public:
    enum class NameFormat {
        HexRgb = QColor::HexRgb,
        HexArgb = QColor::HexArgb
    };
    Q_ENUM(NameFormat)

    enum class Role {
        HexArgbName = Qt::UserRole
    };
    Q_ENUM(Role)

    explicit QColorListModel(QObject *parent = nullptr);
    explicit QColorListModel(const QStringList &colorListNames, QObject *parent = nullptr);
    explicit QColorListModel(const QList<QColor> &colorsList, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex sibling(int row, int column, const QModelIndex &idx) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    Qt::DropActions supportedDropActions() const override;

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QStringList colorListNames() const;
    void setColorListNames(const QStringList &colorListNames);

    QList<QColor> colorsList() const;
    void setColorsList(const QList<QColor> &colors);
};
