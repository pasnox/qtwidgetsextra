#include "QColorLineEdit.h"

class QColorLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QColorLineEditPrivate(QColorLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QColorAction(this)) {
        Q_ASSERT(widget);

        widget->addAction(action, QLineEdit::ActionPosition::LeadingPosition);
        widget->setText(action->colorName(action->color()));
        updateValidator();

        connect(widget, &QLineEdit::textEdited, this, &QColorLineEditPrivate::textEdited);
        connect(widget, &QLineEdit::editingFinished, this, &QColorLineEditPrivate::editingFinished);
        connect(action, &QColorAction::colorChanged, this, &QColorLineEditPrivate::colorChanged);
    }

    void updateValidator() {
        if (action->options().testFlag(QColorAction::ShowAlphaChannel)) {
            widget->setInputMask(QStringLiteral("\\#HHHhhhhh"));
        }
        else {
            widget->setInputMask(QStringLiteral("\\#HHHhhh"));
        }
    }

public slots:
    void textEdited(const QString &text) {
        const QColor color = QColor(text);

        if (color.isValid()) {
            action->setIcon(action->colorIcon(color));
        }
        else {
            action->setIcon(action->colorIcon(action->color()));
        }
    }

    void editingFinished() {
        const QColor color = QColor(widget->text());

        if (color.isValid()) {
            action->setColor(color);
        }
        else {
            action->setIcon(action->colorIcon(action->color()));
            widget->setText(action->colorName(action->color()));
        }
    }

    void colorChanged(const QColor &color) {
        widget->setText(action->colorName(action->color()));
        emit widget->colorChanged(color);
    }

public:
    QColorLineEdit *widget;
    QColorAction *action;
};

QColorLineEdit::QColorLineEdit(QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QColorLineEditPrivate(this))
{
}

QColorLineEdit::QColorLineEdit(const QColor &color, QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QColorLineEditPrivate(this))
{
    d->action->setColor(color);
}

QColorLineEdit::QColorLineEdit(const QString &colorName, QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QColorLineEditPrivate(this))
{
    d->action->setColor(QColor(colorName));
}

QColor QColorLineEdit::color() const
{
    return d->action->color();
}

void QColorLineEdit::setColor(const QColor &color)
{
    d->action->setColor(color);
}

QString QColorLineEdit::caption() const
{
    return d->action->caption();
}

void QColorLineEdit::setCaption(const QString &caption)
{
    d->action->setCaption(caption);
}

QColorAction::ColorDialogOptions QColorLineEdit::options() const
{
    return d->action->options();
}

void QColorLineEdit::setOptions(QColorAction::ColorDialogOptions options)
{
    d->action->setOptions(options);
    d->updateValidator();
}

#include "QColorLineEdit.moc"

