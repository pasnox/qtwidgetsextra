#include "QColorPushButton.h"

class QColorPushButtonPrivate : public QObject {
    Q_OBJECT

public:
    QColorPushButtonPrivate(QColorPushButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QColorAction(this)) {
        Q_ASSERT(widget);

        action->setProperty("button", QVariant::fromValue(widget));
        syncButtonWithAction();

        connect(widget, &QAbstractButton::clicked, action, &QAction::trigger);
        connect(action, &QColorAction::colorChanged, this, &QColorPushButtonPrivate::syncButtonWithAction);
        connect(action, &QColorAction::colorChanged, widget, &QColorPushButton::colorChanged);
    }

public Q_SLOTS:
    void syncButtonWithAction() {
        widget->setIcon(action->icon());
        widget->setText(action->text());
        widget->setToolTip(action->toolTip());
    }

public:
    QColorPushButton *widget;
    QColorAction *action;
};

QColorPushButton::QColorPushButton(QWidget *parent)
    : QPushButton(parent)
    , d(new QColorPushButtonPrivate(this)) {
}

QColorPushButton::QColorPushButton(const QColor &color, QWidget *parent)
    : QPushButton(parent)
    , d(new QColorPushButtonPrivate(this)) {
    d->action->setColor(color);
}

QColorPushButton::QColorPushButton(const QString &colorName, QWidget *parent)
    : QPushButton(parent)
    , d(new QColorPushButtonPrivate(this)) {
    d->action->setColor(QColor(colorName));
}

QColor QColorPushButton::color() const {
    return d->action->color();
}

void QColorPushButton::setColor(const QColor &color) {
    d->action->setColor(color);
}

QString QColorPushButton::caption() const {
    return d->action->caption();
}

void QColorPushButton::setCaption(const QString &caption) {
    d->action->setCaption(caption);
}

QColorAction::ColorDialogOptions QColorPushButton::options() const {
    return d->action->options();
}

void QColorPushButton::setOptions(QColorAction::ColorDialogOptions options) {
    d->action->setOptions(options);
}

#include "QColorPushButton.moc"
