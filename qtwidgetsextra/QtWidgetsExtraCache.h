#ifndef QTWIDGETSEXTRACACHE_H
#define QTWIDGETSEXTRACACHE_H

#include <QString>

class QPixmap;
class QIcon;

namespace QtWidgetsExtraCache
{
    bool cachePixmap(const QString &key, const QPixmap &pixmap);
    QPixmap cachedPixmap(const QString &key);
    bool cacheIcon(const QString &key, const QIcon &icon);
    QIcon cachedIcon(const QString &key);
}

#endif // QTWIDGETSEXTRACACHE_H
