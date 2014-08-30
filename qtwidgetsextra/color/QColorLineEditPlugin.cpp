#include "QColorLineEditPlugin.h"
#include "QColorLineEdit.h"

#include <QtPlugin>

QColorLineEditPlugin::QColorLineEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QColorLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QColorLineEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QColorLineEditPlugin::createWidget(QWidget *parent)
{
    return new QColorLineEdit(parent);
}

QString QColorLineEditPlugin::name() const
{
    return QLatin1String("QColorLineEdit");
}

QString QColorLineEditPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / Color");
}

QIcon QColorLineEditPlugin::icon() const
{
    return QIcon(QString(QLatin1String(":/qt-project.org/formeditor/images/widgets/lineedit.png")));
}

QString QColorLineEditPlugin::toolTip() const
{
    return QLatin1String("A line edit with a tool button that allow to choose a color");
}

QString QColorLineEditPlugin::whatsThis() const
{
    return toolTip();
}

bool QColorLineEditPlugin::isContainer() const
{
    return false;
}

QString QColorLineEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QColorLineEdit\" name=\"colorLineEdit\">\n</widget>\n");
}

QString QColorLineEditPlugin::includeFile() const
{
    return QLatin1String("QColorLineEdit.h");
}

