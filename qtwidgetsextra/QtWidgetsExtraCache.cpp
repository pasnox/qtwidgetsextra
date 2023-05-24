#include "QtWidgetsExtraCache.h"

#include <QPixmap>
#include <QPixmapCache>
#include <QIcon>
#include <QCache>

namespace QtWidgetsExtraCache {
    QCache<qint64, QIcon> cachedIcons;
}

bool QtWidgetsExtraCache::cachePixmap(const QString &key, const QPixmap &pixmap)
{
    if (!QPixmapCache::insert(key, pixmap)) {
        qWarning("%s: Can not cache pixmap with key: %s", Q_FUNC_INFO, qPrintable(key));
        return false;
    }

    return true;
}

QPixmap QtWidgetsExtraCache::cachedPixmap(const QString &key)
{
    QPixmap pixmap;
    QPixmapCache::find(key, &pixmap);
    return pixmap;
}

QPixmap QtWidgetsExtraCache::cachedPixmapColor(const QColor &color, const QSize &size)
{
    const QString key = QString(QStringLiteral("%1-%2x%3-pixmap"))
        .arg(color.name(QColor::HexArgb))
        .arg(size.width())
        .arg(size.height())
    ;
    QPixmap pixmap = QtWidgetsExtraCache::cachedPixmap(key);

    if (pixmap.isNull()) {
        pixmap = QPixmap(size);
        pixmap.fill(color);
        QtWidgetsExtraCache::cachePixmap(key, pixmap);
    }

    return pixmap;
}

bool QtWidgetsExtraCache::cacheIcon(const QString &key, const QIcon &icon)
{
    if (icon.isNull()) {
        qWarning("%s: Can not cache null icon with key: %s", Q_FUNC_INFO, qPrintable(key));
        return false;
    }

    QIcon *ptr = new QIcon(icon);

    if (!cachedIcons.insert(qHash(key), ptr)) {
        qWarning("%s: Can not cache icon with key: %s", Q_FUNC_INFO, qPrintable(key));
        delete ptr;
        return false;
    }

    return true;
}

QIcon QtWidgetsExtraCache::cachedIcon(const QString &key)
{
    QIcon* icon = cachedIcons.object(qHash(key));
    return icon ? *icon : QIcon();
}

QIcon QtWidgetsExtraCache::cachedIconColor(const QColor &color, const QSize &size)
{
    const QString key = QString(QStringLiteral("%1-%2x%3-icon"))
        .arg(color.name(QColor::HexArgb))
        .arg(size.width())
        .arg(size.height())
    ;
    QIcon icon = QtWidgetsExtraCache::cachedIcon(key);

    if (icon.isNull()) {
        QPixmap pixmap = QtWidgetsExtraCache::cachedPixmapColor(color, size);

        if (!pixmap.isNull()) {
            icon = QIcon(pixmap);
            QtWidgetsExtraCache::cacheIcon(key, icon);
        }
    }

    return icon;
}
