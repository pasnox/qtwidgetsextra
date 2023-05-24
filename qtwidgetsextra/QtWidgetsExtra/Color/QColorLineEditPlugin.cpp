#include "QColorLineEditPlugin.h"
#include "QColorLineEdit.h"

#include <QtPlugin>

QColorLineEditPlugin::QColorLineEditPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
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
    return QStringLiteral("QColorLineEdit");
}

QString QColorLineEditPlugin::group() const
{
    return QStringLiteral("Qt Widgets Extra / Color");
}

QIcon QColorLineEditPlugin::icon() const
{
    return QIcon(QStringLiteral(":/qt-project.org/formeditor/images/widgets/lineedit.png"));
}

QString QColorLineEditPlugin::toolTip() const
{
    return QStringLiteral("A line edit with a tool button that allow to choose a color");
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
    return QStringLiteral("<widget class=\"QColorLineEdit\" name=\"colorLineEdit\">\n</widget>\n");
}

QString QColorLineEditPlugin::includeFile() const
{
    return QStringLiteral("QColorLineEdit.h");
}
