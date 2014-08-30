#include "QColorComboBoxPlugin.h"
#include "QColorComboBox.h"

#include <QtPlugin>

QColorComboBoxPlugin::QColorComboBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QColorComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QColorComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QColorComboBoxPlugin::createWidget(QWidget *parent)
{
    return new QColorComboBox(parent);
}

QString QColorComboBoxPlugin::name() const
{
    return QLatin1String("QColorComboBox");
}

QString QColorComboBoxPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / Color");
}

QIcon QColorComboBoxPlugin::icon() const
{
    return QIcon();
}

QString QColorComboBoxPlugin::toolTip() const
{
    return QLatin1String("A combo box that present a QColorListModel");
}

QString QColorComboBoxPlugin::whatsThis() const
{
    return toolTip();
}

bool QColorComboBoxPlugin::isContainer() const
{
    return false;
}

QString QColorComboBoxPlugin::domXml() const
{
    return QLatin1String(
        "<widget class=\"QColorComboBox\" name=\"colorComboBox\">\n"
            "<property name=\"colorNames\">\n"
            "<stringlist>\n"
             "<string>#ff0000</string>\n"
             "<string>#00ff00</string>\n"
             "<string>#0000ff</string>\n"
            "</stringlist>\n"
           "</property>\n"
           "<property name=\"currentIndex\">\n"
            "<number>0</number>\n"
           "</property>\n"
        "</widget>\n"
    );
}

QString QColorComboBoxPlugin::includeFile() const
{
    return QLatin1String("QColorComboBox.h");
}

