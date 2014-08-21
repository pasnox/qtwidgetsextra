#include "QColorLineEdit.h"

#include <QHBoxLayout>
#include <QStyle>
#include <QRegExpValidator>

class QColorLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QColorLineEditPrivate(QColorLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , button(new QColorToolButton(widget))
    {
        Q_ASSERT(widget);

        const int frameMargin = widget->style()->pixelMetric(QStyle::PM_DefaultFrameWidth, 0, widget);
        const int height = widget->sizeHint().height() -(frameMargin *4);
        QMargins margins(widget->textMargins());

        button->setCursor(Qt::ArrowCursor);
        button->setEmbeded(true);
        button->setFixedSize(height, height);

        margins.setLeft(margins.left() +(frameMargin *4));

        QHBoxLayout* hl = new QHBoxLayout(widget);
        hl->setSpacing(0);
        hl->setContentsMargins(margins);
        hl->addWidget(button);
        hl->addStretch();

        margins.setLeft(margins.left() +height);
        widget->setTextMargins(margins);

        updateValidator();

        connect(widget, SIGNAL(textEdited(QString)), this, SLOT(textEdited(QString)));
        connect(widget, SIGNAL(editingFinished()), this, SLOT(editingFinished()));
        connect(button, SIGNAL(colorChanged(QColor)), this, SLOT(colorChanged(QColor)));
        connect(button, SIGNAL(colorChanged(QColor)), widget, SIGNAL(colorChanged(QColor)));
    }

    void updateValidator() {
        if (button->options() & QColorToolButton::ShowAlphaChannel) {
            widget->setValidator(new QRegExpValidator(QRegExp(QLatin1String("#[A-Fa-f0-9]{2,8}")), this));
        }
        else {
            widget->setValidator(new QRegExpValidator(QRegExp(QLatin1String("#[A-Fa-f0-9]{2,6}")), this));
        }
    }

public slots:
    void textEdited(const QString &text) {
        button->setIcon(button->colorIcon(QColor(text)));
    }

    void editingFinished() {
        button->setColor(QColor(widget->text()));
    }

    void colorChanged(const QColor &color) {
        Q_UNUSED(color);

        if (widget->text() != button->text()) {
            widget->setText(button->text());
        }
    }

public:
    QColorLineEdit* widget;
    QColorToolButton* button;
};

QColorLineEdit::QColorLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , d(new QColorLineEditPrivate(this))
{
}

QColorLineEdit::QColorLineEdit(const QColor &color, QWidget *parent)
    : QLineEdit(parent)
    , d(new QColorLineEditPrivate(this))
{
    d->button->setColor(color);
}

QColor QColorLineEdit::color() const
{
    return d->button->color();
}

void QColorLineEdit::setColor(const QColor &color)
{
    d->button->setColor(color);
}

QString QColorLineEdit::caption() const
{
    return d->button->caption();
}

void QColorLineEdit::setCaption(const QString &caption)
{
    d->button->setCaption(caption);
}

QColorToolButton::ColorDialogOptions QColorLineEdit::options() const
{
    return d->button->options();
}

void QColorLineEdit::setOptions(QColorToolButton::ColorDialogOptions options)
{
    d->button->setOptions(options);
    d->updateValidator();
}

void QColorLineEdit::resetColor()
{
    QMetaObject::invokeMethod(d->button, "resetColor");
}

void QColorLineEdit::resetCaption()
{
    QMetaObject::invokeMethod(d->button, "resetCaption");
}

void QColorLineEdit::resetOptions()
{
    QMetaObject::invokeMethod(d->button, "resetOptions");
    d->updateValidator();
}

#include "QColorLineEdit.moc"
