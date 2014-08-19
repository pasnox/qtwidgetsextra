#include "QColorToolButtonPlugin.h"
#include "QColorToolButton.h"

#include <QtPlugin>

QColorToolButtonPlugin::QColorToolButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QColorToolButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QColorToolButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QColorToolButtonPlugin::createWidget(QWidget *parent)
{
    return new QColorToolButton(parent);
}

QString QColorToolButtonPlugin::name() const
{
    return QLatin1String("QColorToolButton");
}

QString QColorToolButtonPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / Color");
}

QIcon QColorToolButtonPlugin::icon() const
{
    return QIcon();
}

QString QColorToolButtonPlugin::toolTip() const
{
    return QLatin1String("A tool button that present a QColorDialog on click");
}

QString QColorToolButtonPlugin::whatsThis() const
{
    return toolTip();
}

bool QColorToolButtonPlugin::isContainer() const
{
    return false;
}

QString QColorToolButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QColorToolButton\" name=\"colorToolButton\">\n</widget>\n");
}

QString QColorToolButtonPlugin::includeFile() const
{
    return QLatin1String("QColorToolButton.h");
}

