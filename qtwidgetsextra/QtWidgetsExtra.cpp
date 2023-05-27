#include "QtWidgetsExtra.h"
#include "generated/pluginsHeaders.h"

QtWidgetsExtra::QtWidgetsExtra(QObject *parent)
    : QObject(parent)
{
#include "generated/pluginsNew.h"
}

QList<QDesignerCustomWidgetInterface*> QtWidgetsExtra::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(QtWidgetsExtra, QtWidgetsExtra)
#endif // QT_VERSION < 0x050000
