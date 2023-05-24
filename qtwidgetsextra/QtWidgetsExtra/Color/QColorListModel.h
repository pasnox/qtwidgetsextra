#ifndef QCOLORLISTMODEL_H
#define QCOLORLISTMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QColor>

// NOTE: This class duplicate QColor::NameFormat because this is not a Qt namespace available enum for Qt Designer.

class QColorListModel : public QAbstractListModel
{
    Q_OBJECT
    class QColorListModelPrivate *d;
    Q_ENUMS(NameFormat)

public:
    enum NameFormat {
        HexRgb = QColor::HexRgb,
        HexArgb = QColor::HexArgb
    };

    enum CustomRoles {
        HexArgbName = Qt::UserRole
    };

    explicit QColorListModel(QObject *parent = 0);
    explicit QColorListModel(const QStringList &colorListNames, QObject *parent = 0);
    explicit QColorListModel(const QList<QColor> &colorsList, QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex sibling(int row, int column, const QModelIndex &idx) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    virtual Qt::DropActions supportedDropActions() const;

    QColorListModel::NameFormat nameFormat() const;
    void setNameFormat(QColorListModel::NameFormat nameFormat);

    QStringList colorListNames() const;
    void setColorListNames(const QStringList &colorListNames);

    QList<QColor> colorsList() const;
    void setColorsList(const QList<QColor> &colors);
};

#endif // QCOLORLISTMODEL_H
