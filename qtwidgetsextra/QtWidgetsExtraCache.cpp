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
