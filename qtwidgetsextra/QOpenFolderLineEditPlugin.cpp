#include "QOpenFolderLineEditPlugin.h"
#include "QOpenFolderLineEdit.h"

#include <QtPlugin>
#include <QApplication>
#include <QStyle>

QOpenFolderLineEditPlugin::QOpenFolderLineEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QOpenFolderLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QOpenFolderLineEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QOpenFolderLineEditPlugin::createWidget(QWidget *parent)
{
    return new QOpenFolderLineEdit(parent);
}

QString QOpenFolderLineEditPlugin::name() const
{
    return QLatin1String("QOpenFolderLineEdit");
}

QString QOpenFolderLineEditPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra");
}

QIcon QOpenFolderLineEditPlugin::icon() const
{
    return QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton);
}

QString QOpenFolderLineEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QOpenFolderLineEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QOpenFolderLineEditPlugin::isContainer() const
{
    return false;
}

QString QOpenFolderLineEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QOpenFolderLineEdit\" name=\"openFolderLineEdit\">\n</widget>\n");
}

QString QOpenFolderLineEditPlugin::includeFile() const
{
    return QLatin1String("QOpenFolderLineEdit.h");
}

