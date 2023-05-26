#pragma once

#include <QString>

#include <QtWidgetsExtraLibExport.h>

class QPixmap;
class QIcon;
class QColor;
class QSize;

namespace QtWidgetsExtraCache
{
    QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT bool cachePixmap(const QString &key, const QPixmap &pixmap);
    QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QPixmap cachedPixmap(const QString &key);
    QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QPixmap cachedPixmapColor(const QColor &color, const QSize &size);
    QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT bool cacheIcon(const QString &key, const QIcon &icon);
    QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QIcon cachedIcon(const QString &key);
    QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QIcon cachedIconColor(const QColor &color, const QSize &size);
}
