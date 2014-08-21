#include "QColorToolButton.h"

class QColorToolButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QColorToolButtonPrivate(QColorToolButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , color(QColor(Qt::black))
        , options(0)
    {
        Q_ASSERT(widget);

        connect(widget, SIGNAL(clicked()), this, SLOT(clicked()));
    }

    void updateIcon() {
        widget->setIcon(widget->colorIcon(color));
        widget->setText((options & QColorToolButton::ShowAlphaChannel) ? color.name(QColor::HexArgb) : color.name(QColor::HexRgb));
        widget->setToolTip(widget->text());
    }

    void resetColor() {
        widget->setColor(QColor(Qt::black));
    }

    void resetCaption() {
        caption.clear();
    }

    void resetOptions() {
        options = 0;
    }

public slots:
    void clicked() {
        const QColor newColor = QColorDialog::getColor(color, widget->window(), caption, QColorDialog::ColorDialogOptions(int(options)));

        if (newColor.isValid()) {
            widget->setColor(newColor);
        }
    }

public:
    QColorToolButton* widget;
    bool alphaEnabled;
    QColor color;
    QString caption;
    QColorToolButton::ColorDialogOptions options;
};

QColorToolButton::QColorToolButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QColorToolButtonPrivate(this))
{
    d->updateIcon();
}

QColorToolButton::QColorToolButton(const QColor &color, QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QColorToolButtonPrivate(this))
{
    d->color = color;
    d->updateIcon();
}

QColor QColorToolButton::color() const
{
    return d->color;
}

void QColorToolButton::setColor(const QColor &color)
{
    if (d->color == color) {
        return;
    }

    d->color = color;
    d->updateIcon();
    emit colorChanged(d->color);
}

QString QColorToolButton::caption() const
{
    return d->caption;
}

void QColorToolButton::setCaption(const QString &caption)
{
    d->caption = caption;
}

QColorToolButton::ColorDialogOptions QColorToolButton::options() const
{
    return d->options;
}

void QColorToolButton::setOptions(QColorToolButton::ColorDialogOptions options)
{
    d->options = options;
}

QIcon QColorToolButton::colorIcon(const QColor &color) const
{
    QPixmap icon(iconSize());
    icon.fill(color);
    return QIcon(icon);
}

void QColorToolButton::paintEvent(QPaintEvent *event)
{
    if (icon().availableSizes().value(0) != iconSize()) {
        d->updateIcon();
    }

    QEmbedableButton::paintEvent(event);
}

void QColorToolButton::resetColor()
{
    d->resetColor();
}

void QColorToolButton::resetCaption()
{
    d->resetCaption();
}

void QColorToolButton::resetOptions()
{
    d->resetOptions();
}

#include "QColorToolButton.moc"
