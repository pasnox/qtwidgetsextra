#include "QButtonGroupBoxPlugin.h"
#include "QButtonGroupBox.h"

#include <QtPlugin>
#include <QApplication>
#include <QStyle>

QButtonGroupBoxPlugin::QButtonGroupBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QButtonGroupBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QButtonGroupBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QButtonGroupBoxPlugin::createWidget(QWidget *parent)
{
    return new QButtonGroupBox(parent);
}

QString QButtonGroupBoxPlugin::name() const
{
    return QLatin1String("QButtonGroupBox");
}

QString QButtonGroupBoxPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / Group Box");
}

QIcon QButtonGroupBoxPlugin::icon() const
{
    return QIcon(QLatin1String(":/qt-project.org/formeditor/images/widgets/groupbox.png"));
}

QString QButtonGroupBoxPlugin::toolTip() const
{
    return QLatin1String("A widget to manage multiple checkable buttons");
}

QString QButtonGroupBoxPlugin::whatsThis() const
{
    return toolTip();
}

bool QButtonGroupBoxPlugin::isContainer() const
{
    return false;
}

QString QButtonGroupBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QButtonGroupBox\" name=\"buttonGroupBox\">\n</widget>\n");
}

QString QButtonGroupBoxPlugin::includeFile() const
{
    return QLatin1String("QButtonGroupBox.h");
}
