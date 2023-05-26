#pragma once

#include <QStyledItemDelegate>

#include "Generator.h"

class QComboBox;

class GeneratorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    enum Columns {
        ColumnParameterType,
        ColumnType,
        ColumnName,
        ColumnDefaultValue,
        ColumnSignal,
        ColumnProperty
    };
    Q_ENUM(Columns)

    explicit GeneratorDelegate(QObject *parent = nullptr);

    virtual QWidget *createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    virtual void setEditorData( QWidget *editor, const QModelIndex &index ) const;
    virtual void setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const;
    virtual QSize sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const;
    virtual void updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const;

    static const QHash<QString, Generator::ParameterType>& constTypes();
};
