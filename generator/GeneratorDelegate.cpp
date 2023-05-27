#include "GeneratorDelegate.h"

#include <QComboBox>

GeneratorDelegate::GeneratorDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

QWidget *GeneratorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
    switch (static_cast<GeneratorDelegate::Column>(index.column())) {
    case GeneratorDelegate::Column::Type: {
        const QHash<QString, Generator::ParameterType> &types = GeneratorDelegate::constTypes();
        QComboBox *cb = new QComboBox(parent);

        cb->setEditable(true);

        foreach (const QString &type, types.keys()) {
            cb->addItem(type, QVariant::fromValue(types[type]));
        }

        return cb;
    }

    case GeneratorDelegate::Column::Name:
        return QStyledItemDelegate::createEditor(parent, option, index);

    case GeneratorDelegate::Column::ParameterType: {
        QComboBox *cb = new QComboBox(parent);

        cb->addItem(QStringLiteral("Variable"), QVariant::fromValue(Generator::ParameterType::Variable));
        cb->addItem(QStringLiteral("Reference"), QVariant::fromValue(Generator::ParameterType::Reference));
        cb->addItem(QStringLiteral("Pointer"), QVariant::fromValue(Generator::ParameterType::Pointer));

        return cb;
    }

    case GeneratorDelegate::Column::DefaultValue:
        return QStyledItemDelegate::createEditor(parent, option, index);

    case GeneratorDelegate::Column::Signal:
    case GeneratorDelegate::Column::Property:
        break;
    }

    return 0;
}

void GeneratorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    switch (static_cast<GeneratorDelegate::Column>(index.column())) {
    case GeneratorDelegate::Column::Type: {
        QComboBox *cb = qobject_cast<QComboBox *>(editor);
        const QString type = index.data(Qt::DisplayRole).toString();
        int index = cb->findText(type);

        if (index == -1) {
            cb->addItem(type);
            index = cb->count() - 1;
        }

        cb->setCurrentIndex(index);
        break;
    }

    case GeneratorDelegate::Column::ParameterType: {
        const auto type = index.data(Qt::DisplayRole);
        QComboBox *cb = qobject_cast<QComboBox *>(editor);
        int index = cb->findData(type);

        if (index == -1) {
            Q_ASSERT(0);
        }

        cb->setCurrentIndex(index);
        break;
    }

    case GeneratorDelegate::Column::Name:
    case GeneratorDelegate::Column::DefaultValue:
    case GeneratorDelegate::Column::Signal:
    case GeneratorDelegate::Column::Property:
        QStyledItemDelegate::setEditorData(editor, index);
        break;
    }
}

void GeneratorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    switch (static_cast<GeneratorDelegate::Column>(index.column())) {
    case GeneratorDelegate::Column::Type: {
        QComboBox *cb = qobject_cast<QComboBox *>(editor);
        model->setData(index, cb->currentText(), Qt::DisplayRole);
        model->setData(index.sibling(index.row(), static_cast<int>(GeneratorDelegate::Column::ParameterType)),
                       QVariant::fromValue(constTypes().value(cb->currentText(), Generator::ParameterType::Variable)),
                       Qt::DisplayRole);
        break;
    }

    case GeneratorDelegate::Column::ParameterType: {
        QComboBox *cb = qobject_cast<QComboBox *>(editor);
        model->setData(index, cb->currentData().toInt(), Qt::DisplayRole);
        break;
    }

    case GeneratorDelegate::Column::Name:
    case GeneratorDelegate::Column::DefaultValue:
    case GeneratorDelegate::Column::Signal:
    case GeneratorDelegate::Column::Property:
        QStyledItemDelegate::setModelData(editor, model, index);
        break;
    }
}

QSize GeneratorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(option, index);
}

void GeneratorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const {
    switch (static_cast<GeneratorDelegate::Column>(index.column())) {
    case GeneratorDelegate::Column::Type: {
        QRect r = option.rect;
        r.setWidth(editor->minimumSizeHint().width());
        editor->setGeometry(r);
        break;
    }

    case GeneratorDelegate::Column::Name:
    case GeneratorDelegate::Column::ParameterType:
    case GeneratorDelegate::Column::DefaultValue:
    case GeneratorDelegate::Column::Signal:
    case GeneratorDelegate::Column::Property:
        QStyledItemDelegate::updateEditorGeometry(editor, option, index);
        break;
    }
}

const QHash<QString, Generator::ParameterType> &GeneratorDelegate::constTypes() {
    static const QHash<QString, Generator::ParameterType> types {
        {QStringLiteral("QColor"), Generator::ParameterType::Reference},
        {QStringLiteral("QVariant"), Generator::ParameterType::Reference},
        {QStringLiteral("QString"), Generator::ParameterType::Reference},
        {QStringLiteral("QStringList"), Generator::ParameterType::Reference},
        {QStringLiteral("bool"), Generator::ParameterType::Variable},
        {QStringLiteral("QSize"), Generator::ParameterType::Reference},
        {QStringLiteral("QFont"), Generator::ParameterType::Reference},
        {QStringLiteral("QRect"), Generator::ParameterType::Reference},
        {QStringLiteral("QPoint"), Generator::ParameterType::Reference},
        {QStringLiteral("QBrush"), Generator::ParameterType::Reference},
        {QStringLiteral("QPen"), Generator::ParameterType::Reference},
        {QStringLiteral("QObject"), Generator::ParameterType::Pointer},
        {QStringLiteral("QWidget"), Generator::ParameterType::Pointer},
    };

    return types;
}
