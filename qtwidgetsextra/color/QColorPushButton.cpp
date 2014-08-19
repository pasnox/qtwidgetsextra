#include "QColorPushButton.h"

class QColorPushButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QColorPushButtonPrivate(QColorPushButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , color(QColor(Qt::black))
        , options(0)
    {
        Q_ASSERT(widget);

        connect(widget, SIGNAL(clicked()), this, SLOT(clicked()));
    }

    void updateIcon() {
        QPixmap icon(widget->iconSize());
        icon.fill(color);

        widget->setIcon(icon);
        widget->setText((options & QColorDialog::ShowAlphaChannel) ? color.name(QColor::HexArgb) : color.name(QColor::HexRgb));
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
        const QColor newColor = QColorDialog::getColor(color, widget->window(), caption, options);

        if (newColor.isValid()) {
            widget->setColor(newColor);
        }
    }

public:
    QColorPushButton* widget;
    bool alphaEnabled;
    QColor color;
    QString caption;
    QColorDialog::ColorDialogOptions options;
};

QColorPushButton::QColorPushButton(QWidget *parent)
    : QPushButton(parent)
    , d(new QColorPushButtonPrivate(this))
{
    d->updateIcon();
}

QColorPushButton::QColorPushButton(const QColor &color, QWidget *parent)
    : QPushButton(parent)
    , d(new QColorPushButtonPrivate(this))
{
    d->color = color;
    d->updateIcon();
}

QColor QColorPushButton::color() const
{
    return d->color;
}

void QColorPushButton::setColor(const QColor &color)
{
    if (d->color == color) {
        return;
    }

    d->color = color;
    d->updateIcon();
    emit colorChanged(d->color);
}

QString QColorPushButton::caption() const
{
    return d->caption;
}

void QColorPushButton::setCaption(const QString &caption)
{
    d->caption = caption;
}

QColorDialog::ColorDialogOptions QColorPushButton::options() const
{
    return d->options;
}

void QColorPushButton::setOptions(QColorDialog::ColorDialogOptions options)
{
    d->options = options;
}

void QColorPushButton::paintEvent(QPaintEvent *event)
{
    if (icon().availableSizes().value(0) != iconSize()) {
        d->updateIcon();
    }

    QPushButton::paintEvent(event);
}

void QColorPushButton::resetColor()
{
    d->resetColor();
}

void QColorPushButton::resetCaption()
{
    d->resetCaption();
}

void QColorPushButton::resetOptions()
{
    d->resetOptions();
}

#include "QColorPushButton.moc"
