#include "QOpenFolderButtonPlugin.h"
#include "QOpenFolderButton.h"

#include <QtPlugin>
#include <QApplication>
#include <QStyle>

QOpenFolderButtonPlugin::QOpenFolderButtonPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
}

void QOpenFolderButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QOpenFolderButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QOpenFolderButtonPlugin::createWidget(QWidget *parent)
{
    return new QOpenFolderButton(parent);
}

QString QOpenFolderButtonPlugin::name() const
{
    return QLatin1String("QOpenFolderButton");
}

QString QOpenFolderButtonPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / File Dialog");
}

QIcon QOpenFolderButtonPlugin::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_DirIcon);
}

QString QOpenFolderButtonPlugin::toolTip() const
{
    return QLatin1String("A tool button that allow to choose an existing folder");
}

QString QOpenFolderButtonPlugin::whatsThis() const
{
    return toolTip();
}

bool QOpenFolderButtonPlugin::isContainer() const
{
    return false;
}

QString QOpenFolderButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QOpenFolderButton\" name=\"openFolderButton\">\n</widget>\n");
}

QString QOpenFolderButtonPlugin::includeFile() const
{
    return QLatin1String("QOpenFolderButton.h");
}

