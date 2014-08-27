#include "QColorAction.h"
#include "QtWidgetsExtraCache.h"

#include <QAbstractButton>

class QColorActionPrivate : public QObject {
    Q_OBJECT

public:
    QColorActionPrivate(QColorAction *actionP)
        : QObject(actionP)
        , action(actionP)
        , options(0) {
        Q_ASSERT(action);

        connect(action, SIGNAL(triggered()), this, SLOT(triggered()));
    }

public slots:
    void triggered() {
        const QColor newColor = QColorDialog::getColor(color, 0, caption, QColorDialog::ColorDialogOptions(int(options)));

        if (newColor.isValid()) {
            action->setColor(newColor);
        }
    }

public:
    QColorAction *action;
    QColor color;
    QString caption;
    QColorAction::ColorDialogOptions options;
};

QColorAction::QColorAction(QObject *parent)
    : QAction(parent)
    , d(new QColorActionPrivate(this))
{
    setColor(Qt::black);
}

QColorAction::QColorAction(const QColor &color, QObject *parent)
    : QAction(parent)
    , d(new QColorActionPrivate(this))
{
    setColor(color);
}

QColorAction::QColorAction(const QString &colorName, QObject *parent)
    : QAction(parent)
    , d(new QColorActionPrivate(this))
{
    setColor(QColor(colorName));
}

QColor QColorAction::color() const
{
    return d->color;
}

void QColorAction::setColor(const QColor &color)
{
    if (color.alpha() != 255 && !d->options.testFlag(QColorAction::ShowAlphaChannel)) {
        qWarning("%s: Trying to set a color with alpha with options not allowing alpha", Q_FUNC_INFO);
    }

    if (d->color == color) {
        return;
    }

    d->color = color;
    setIcon(colorIcon(d->color));
    setText(colorName(color));
    setToolTip(text());
    emit colorChanged(d->color);
}

QString QColorAction::caption() const
{
    return d->caption;
}

void QColorAction::setCaption(const QString &caption)
{
    d->caption = caption;
}

QColorAction::ColorDialogOptions QColorAction::options() const
{
    return d->options;
}

void QColorAction::setOptions(QColorAction::ColorDialogOptions options)
{
    d->options = options;
}

QIcon QColorAction::colorIcon(const QColor &color) const
{
    QAbstractButton* button = property("button").value<QAbstractButton*>();
    const QSize size = (button ? button->iconSize() : QSize(24, 24)) *2;
    const QString key = QString(QLatin1String("%1-%2x%3"))
        .arg(color.name(QColor::HexArgb))
        .arg(size.width())
        .arg(size.height())
    ;
    QIcon icon = QtWidgetsExtraCache::cachedIcon(key);

    if (icon.isNull()) {
        QPixmap pixmap = QtWidgetsExtraCache::cachedPixmap(key);

        if (pixmap.isNull()) {
            pixmap = QPixmap(size);
            pixmap.fill(color);
            QtWidgetsExtraCache::cachePixmap(key, pixmap);
        }

        if (!pixmap.isNull()) {
            icon = QIcon(pixmap);
            QtWidgetsExtraCache::cacheIcon(key, icon);
        }
    }

    return icon;
}

QString QColorAction::colorName(const QColor &color) const
{
    return color.name(d->options.testFlag(QColorAction::ShowAlphaChannel) ? QColor::HexArgb : QColor::HexRgb);
}

#include "QColorAction.moc"
