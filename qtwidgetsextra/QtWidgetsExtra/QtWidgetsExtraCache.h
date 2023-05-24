#ifndef QTWIDGETSEXTRACACHE_H
#define QTWIDGETSEXTRACACHE_H

#include <QString>

class QPixmap;
class QIcon;
class QColor;
class QSize;

namespace QtWidgetsExtraCache
{
    bool cachePixmap(const QString &key, const QPixmap &pixmap);
    QPixmap cachedPixmap(const QString &key);
    QPixmap cachedPixmapColor(const QColor &color, const QSize &size);
    bool cacheIcon(const QString &key, const QIcon &icon);
    QIcon cachedIcon(const QString &key);
    QIcon cachedIconColor(const QColor &color, const QSize &size);
}

#endif // QTWIDGETSEXTRACACHE_H
