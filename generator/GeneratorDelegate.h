#pragma once

#include "Generator.h"

#include <QStyledItemDelegate>

class QComboBox;

class GeneratorDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    enum class Column {
        ParameterType,
        Type,
        Name,
        DefaultValue,
        Signal,
        Property
    };
    Q_ENUM(Column)

    explicit GeneratorDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    static const QHash<QString, Generator::ParameterType> &constTypes();
};
