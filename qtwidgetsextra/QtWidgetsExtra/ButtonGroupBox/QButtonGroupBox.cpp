#include "QButtonGroupBox.h"
#include "QtWidgetsExtra/ButtonGroupBox/QAbstractButtonListModel.h"

#include <QButtonGroup>
#include <QBoxLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QStyle>

class QButtonGroupBoxPrivate : public QObject {
    Q_OBJECT

public:
    QButtonGroupBoxPrivate(QButtonGroupBox *widget)
        : QObject(widget)
        , widget(widget)
        , layout(new QBoxLayout(QBoxLayout::TopToBottom, widget))
        , group(new QButtonGroup(this))
        , model(new QAbstractButtonListModel(this))
        , type(QButtonGroupBox::CheckBox) {
        Q_ASSERT(widget);
        const int hint = widget->style()->pixelMetric(QStyle::PM_ButtonIconSize);
        iconSize = QSize(hint, hint);

        connect(model, &QAbstractButtonListModel::rowsInserted,
                this, [this](const QModelIndex &parent, int first, int last) {
            Q_UNUSED(parent);

            for (int i = first; i <= last; ++i) {
                createButton(i);
            }
        });
        connect(model, &QAbstractButtonListModel::dataChanged,
                this, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
            for (int i = topLeft.row(); i <= bottomRight.row(); ++i) {
                updateButton(i, roles);
            }
        });
        connect(model, &QAbstractButtonListModel::rowsRemoved,
                this, [this](const QModelIndex &parent, int first, int last) {
            Q_UNUSED(parent);

            for (int i = last; i >= first; --i) {
                removeButton(i);
            }
        });

        connect(group, qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked),
                this, [this](QAbstractButton *button) {
            Q_EMIT this->widget->buttonClicked(layout->indexOf(button), group->id(button));
        });
        connect(group, qOverload<QAbstractButton *>(&QButtonGroup::buttonPressed),
                this, [this](QAbstractButton *button) {
            Q_EMIT this->widget->buttonPressed(layout->indexOf(button), group->id(button));
        });
        connect(group, qOverload<QAbstractButton *>(&QButtonGroup::buttonReleased),
                this, [this](QAbstractButton *button) {
            Q_EMIT this->widget->buttonReleased(layout->indexOf(button), group->id(button));
        });
        connect(group, qOverload<QAbstractButton *, bool>(&QButtonGroup::buttonToggled),
                this, [this](QAbstractButton *button, bool checked) {
            const int index = layout->indexOf(button);
            this->model->setData(this->model->index(index), checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
            Q_EMIT this->widget->buttonToggled(index, group->id(button), checked);
        });
    }

    void resetButtons() {
        for (int i = 0; i < model->rowCount(); ++i) {
            removeButton(i);
            createButton(i);
        }
    }

    void createButton(int index) {
        QAbstractButton *button = widget->createButton();
        Q_ASSERT(button);

        button->setCheckable(true);
        button->setIconSize(iconSize);

        group->addButton(button, model->data(model->index(index), QAbstractButtonListModel::IdRole).toInt());
        layout->insertWidget(index, button);

        updateButton(index);
    }

    void updateButton(int index, const QVector<int> &roles = {}) {
        Q_UNUSED(roles);

        const QButtonGroupBox::Button data = model->itemData(model->index(index));
        QAbstractButton *button = qobject_cast<QAbstractButton *>(layout->itemAt(index)->widget());
        Q_ASSERT(button);

        group->setId(button, data.value(QAbstractButtonListModel::IdRole).toInt());

        button->setChecked(data.value(Qt::CheckStateRole, Qt::Unchecked).value<Qt::CheckState>() == Qt::Checked);
        button->setIcon(data.value(Qt::DecorationRole).value<QIcon>());
        button->setText(data.value(Qt::DisplayRole).toString());
        button->setToolTip(data.value(Qt::ToolTipRole).toString());
        button->setWhatsThis(data.value(Qt::WhatsThisRole).toString());
        button->setStatusTip(data.value(Qt::StatusTipRole).toString());
        button->setAccessibleName(data.value(Qt::AccessibleTextRole).toString());
        button->setAccessibleDescription(data.value(Qt::AccessibleDescriptionRole).toString());
        button->setShortcut(data.value(QAbstractButtonListModel::ShortcutRole).value<QKeySequence>());

        const QVariant font = data.value(Qt::FontRole);
        if (font.isValid()) {
            button->setFont(font.value<QFont>());
        }

        // Exclusive group would not undeck the checked button
        if (button->isChecked() != (data.value(Qt::CheckStateRole, Qt::Unchecked).value<Qt::CheckState>() == Qt::Checked)) {
            model->setData(model->index(index), button->isChecked() ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
        }
    }

    void removeButton(int index) {
        QAbstractButton *button = qobject_cast<QAbstractButton *>(layout->itemAt(index)->widget());
        Q_ASSERT(button);

        layout->removeWidget(button);
        group->removeButton(button);
        button->deleteLater();
    }

public:
    QButtonGroupBox *widget;
    QBoxLayout *layout;
    QButtonGroup *group;
    QAbstractButtonListModel *model;
    QButtonGroupBox::Type type;
    QSize iconSize;
};

QButtonGroupBox::QButtonGroupBox(QWidget *parent)
    : QGroupBox(parent)
    , d(new QButtonGroupBoxPrivate(this))
{
}

Qt::Orientation QButtonGroupBox::orientation() const
{
    return d->layout->direction() == QBoxLayout::LeftToRight
            ? Qt::Horizontal
            : Qt::Vertical;
}

void QButtonGroupBox::setOrientation(Qt::Orientation orientation)
{
    d->layout->setDirection(orientation == Qt::Horizontal
                             ? QBoxLayout::LeftToRight
                             : QBoxLayout::TopToBottom);
}

QButtonGroupBox::Type QButtonGroupBox::type() const
{
    return d->type;
}

void QButtonGroupBox::setType(QButtonGroupBox::Type type)
{
    if (d->type == type) {
        return;
    }

    d->type = type;
    d->resetButtons();
}

QSize QButtonGroupBox::iconSize() const
{
    return d->iconSize;
}

void QButtonGroupBox::setIconSize(const QSize &iconSize)
{
    if (d->iconSize == iconSize) {
        return;
    }

    d->iconSize = iconSize;

    if (!d->layout->isEmpty()) {
        const auto buttons = d->group->buttons();

        for (QAbstractButton *button: buttons) {
            button->setIconSize(d->iconSize);
        }
    }
}

bool QButtonGroupBox::exclusive() const
{
    return d->group->exclusive();
}

void QButtonGroupBox::setExclusive(bool exclusive)
{
    d->group->setExclusive(exclusive);
}

void QButtonGroupBox::insertButton(int index, const QButtonGroupBox::Button &button)
{
    if (d->model->insertRow(index)) {
        d->model->setItemData(d->model->index(index), button);
    }
}

void QButtonGroupBox::addButton(const QButtonGroupBox::Button &button)
{
    insertButton(count(), button);
}

void QButtonGroupBox::removeButton(int index)
{
    d->model->removeRow(index);
}

QVariant QButtonGroupBox::buttonData(int index, int role) const
{
    return d->model->data(d->model->index(index), role);
}

void QButtonGroupBox::setButtonData(int index, int role, const QVariant &data)
{
    d->model->setData(d->model->index(index), data, role);
}

void QButtonGroupBox::clear()
{
    d->model->clear();
}

int QButtonGroupBox::count() const
{
    return d->layout->count();
}

bool QButtonGroupBox::isEmpty() const
{
    return d->layout->isEmpty();
}

int QButtonGroupBox::checkedIndex() const
{
    return d->layout->indexOf(d->group->checkedButton());
}

int QButtonGroupBox::checkedId() const
{
    return d->group->checkedId();
}

QStringList QButtonGroupBox::items() const
{
    QStringList items;

    for (int i = 0; i < count(); ++i) {
        items << d->model->index(i).data(Qt::DisplayRole).toString();
    }

    return items;
}

void QButtonGroupBox::setItems(const QStringList &items)
{
    clear();

    for (const QString &item: items) {
        QButtonGroupBox::Button button;
        button[Qt::DisplayRole] = item;
        addButton(button);
    }
}

QAbstractButton *QButtonGroupBox::createButton() const
{
    switch (d->type) {
    case QButtonGroupBox::CheckBox:
        return new QCheckBox;
    case QButtonGroupBox::RadioBox:
        return new QRadioButton;
    default:
        Q_UNREACHABLE();
    }

    return nullptr;
}

#include "QButtonGroupBox.moc"
