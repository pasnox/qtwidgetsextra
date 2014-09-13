#include "GeneratorDelegate.h"

#include <QComboBox>

GeneratorDelegate::GeneratorDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *GeneratorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column()) {
        case GeneratorDelegate::ColumnType: {
            const QHash<QString, Generator::ParameterType>& types = GeneratorDelegate::constTypes();
            QComboBox *cb = new QComboBox(parent);

            cb->setEditable(true);

            foreach (const QString &type, types.keys()) {
                cb->addItem(type, types[type]);
            }

            return cb;
        }

        case GeneratorDelegate::ColumnName:
            return QStyledItemDelegate::createEditor(parent, option, index);

        case GeneratorDelegate::ColumnParameterType: {
            QComboBox *cb = new QComboBox(parent);

            cb->addItem(QString("Variable"), Generator::Variable);
            cb->addItem(QString("Reference"), Generator::Reference);
            cb->addItem(QString("Pointer"), Generator::Pointer);

            return cb;
        }

        case GeneratorDelegate::ColumnDefaultValue:
            return QStyledItemDelegate::createEditor(parent, option, index);

        case GeneratorDelegate::ColumnSignal:
        case GeneratorDelegate::ColumnProperty:
            break;
    }

    return 0;
}

void GeneratorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch (index.column()) {
        case GeneratorDelegate::ColumnType: {
            QComboBox* cb = qobject_cast<QComboBox*>(editor);
            const QString type = index.data(Qt::DisplayRole).toString();
            int index = cb->findText(type);

            if (index == -1) {
                cb->addItem(type);
                index = cb->count() -1;
            }

            cb->setCurrentIndex(index);
            break;
        }

        case GeneratorDelegate::ColumnParameterType: {
            const Generator::ParameterType type = Generator::ParameterType(index.data(Qt::DisplayRole).toInt());
            QComboBox* cb = qobject_cast<QComboBox*>(editor);
            int index = cb->findData(type);

            if (index == -1) {
                Q_ASSERT(0);
            }

            cb->setCurrentIndex(index);
            break;
        }

        case GeneratorDelegate::ColumnName:
        case GeneratorDelegate::ColumnDefaultValue:
        case GeneratorDelegate::ColumnSignal:
        case GeneratorDelegate::ColumnProperty:
            QStyledItemDelegate::setEditorData(editor, index);
            break;
    }
}

void GeneratorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch (index.column()) {
        case GeneratorDelegate::ColumnType: {
            QComboBox* cb = qobject_cast<QComboBox*>(editor);
            model->setData(index, cb->currentText(), Qt::DisplayRole);
            model->setData(index.sibling(index.row(), GeneratorDelegate::ColumnParameterType), constTypes().value(cb->currentText(), Generator::Variable), Qt::DisplayRole);
            break;
        }

        case GeneratorDelegate::ColumnParameterType: {
            QComboBox* cb = qobject_cast<QComboBox*>(editor);
            model->setData(index, cb->currentData().toInt(), Qt::DisplayRole);
            break;
        }

        case GeneratorDelegate::ColumnName:
        case GeneratorDelegate::ColumnDefaultValue:
        case GeneratorDelegate::ColumnSignal:
        case GeneratorDelegate::ColumnProperty:
            QStyledItemDelegate::setModelData(editor, model, index);
            break;
    }
}

QSize GeneratorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

void GeneratorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column()) {
        case GeneratorDelegate::ColumnType: {
            QRect r = option.rect;
            r.setWidth(editor->minimumSizeHint().width());
            editor->setGeometry(r);
            break;
        }

        case GeneratorDelegate::ColumnName:
        case GeneratorDelegate::ColumnParameterType:
        case GeneratorDelegate::ColumnDefaultValue:
        case GeneratorDelegate::ColumnSignal:
        case GeneratorDelegate::ColumnProperty:
            QStyledItemDelegate::updateEditorGeometry(editor, option, index);
            break;
    }
}

const QHash<QString, Generator::ParameterType>& GeneratorDelegate::constTypes()
{
    static QHash<QString, Generator::ParameterType> types;

    if (types.isEmpty()) {
        types[ "QColor" ] = Generator::Reference;
        types[ "QVariant" ] = Generator::Reference;
        types[ "QString" ] = Generator::Reference;
        types[ "QStringList" ] = Generator::Reference;
        types[ "bool" ] = Generator::Variable;
        types[ "QSize" ] = Generator::Reference;
        types[ "QFont" ] = Generator::Reference;
        types[ "QRect" ] = Generator::Reference;
        types[ "QPoint" ] = Generator::Reference;
        types[ "QBrush" ] = Generator::Reference;
        types[ "QPen" ] = Generator::Reference;
        types[ "QObject" ] = Generator::Pointer;
        types[ "QWidget" ] = Generator::Pointer;
    }

    return types;
}
