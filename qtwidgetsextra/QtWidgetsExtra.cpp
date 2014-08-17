#include "QtWidgetsExtra.h"
#include "QOpenFileButtonPlugin.h"
#include "QOpenFileLineEditPlugin.h"
#include "QSaveFileButtonPlugin.h"
#include "QSaveFileLineEditPlugin.h"
#include "QOpenFolderLineEditPlugin.h"

QtWidgetsExtra::QtWidgetsExtra(QObject *parent)
    : QObject(parent)
{
    m_widgets.append(new QOpenFileButtonPlugin(this));
    m_widgets.append(new QOpenFileLineEditPlugin(this));

    m_widgets.append(new QSaveFileButtonPlugin(this));
    m_widgets.append(new QSaveFileLineEditPlugin(this));

    //m_widgets.append(new QOpenFolderButtonPlugin(this));
    //m_widgets.append(new QOpenFolderLineEditPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QtWidgetsExtra::customWidgets() const
{
    return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(QtWidgetsExtra, QtWidgetsExtra)
#endif // QT_VERSION < 0x050000
