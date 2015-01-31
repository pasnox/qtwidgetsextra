#include "QSaveFileButtonPlugin.h"
#include "QSaveFileButton.h"

#include <QtPlugin>
#include <QApplication>
#include <QStyle>

QSaveFileButtonPlugin::QSaveFileButtonPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
}

void QSaveFileButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QSaveFileButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QSaveFileButtonPlugin::createWidget(QWidget *parent)
{
    return new QSaveFileButton(parent);
}

QString QSaveFileButtonPlugin::name() const
{
    return QLatin1String("QSaveFileButton");
}

QString QSaveFileButtonPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / File Dialog");
}

QIcon QSaveFileButtonPlugin::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton);
}

QString QSaveFileButtonPlugin::toolTip() const
{
    return QLatin1String("A tool button that allow to choose a saving file");
}

QString QSaveFileButtonPlugin::whatsThis() const
{
    return toolTip();
}

bool QSaveFileButtonPlugin::isContainer() const
{
    return false;
}

QString QSaveFileButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSaveFileButton\" name=\"saveFileButton\">\n</widget>\n");
}

QString QSaveFileButtonPlugin::includeFile() const
{
    return QLatin1String("QSaveFileButton.h");
}

