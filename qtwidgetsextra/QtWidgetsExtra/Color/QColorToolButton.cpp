#include "QColorToolButton.h"

class QColorToolButtonPrivate : public QObject {
    Q_OBJECT

public:
    explicit QColorToolButtonPrivate(QColorToolButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QColorAction(this)) {
        Q_ASSERT(widget);

        action->setProperty("button", QVariant::fromValue(widget));
        widget->setDefaultAction(action);

        connect(action, &QColorAction::colorChanged, widget, &QColorToolButton::colorChanged);
    }

public:
    QColorToolButton *widget;
    QColorAction *action;
};

QColorToolButton::QColorToolButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QColorToolButtonPrivate(this)) {
}

QColorToolButton::QColorToolButton(const QColor &color, QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QColorToolButtonPrivate(this)) {
    d->action->setColor(color);
}

QColorToolButton::QColorToolButton(const QString &colorName, QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QColorToolButtonPrivate(this)) {
    d->action->setColor(QColor(colorName));
}

QColor QColorToolButton::color() const {
    return d->action->color();
}

void QColorToolButton::setColor(const QColor &color) {
    d->action->setColor(color);
}

QString QColorToolButton::caption() const {
    return d->action->caption();
}

void QColorToolButton::setCaption(const QString &caption) {
    d->action->setCaption(caption);
}

QColorAction::ColorDialogOptions QColorToolButton::options() const {
    return d->action->options();
}

void QColorToolButton::setOptions(QColorAction::ColorDialogOptions options) {
    d->action->setOptions(options);
}

#include "QColorToolButton.moc"
