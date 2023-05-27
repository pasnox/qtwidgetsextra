#include "QUpDownButtonPlugin.h"
#include "QUpDownButton.h"

QUpDownButtonPlugin::QUpDownButtonPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QUpDownButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QUpDownButtonPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QUpDownButtonPlugin::createWidget(QWidget *parent) {
    return new QUpDownButton(parent);
}

QString QUpDownButtonPlugin::name() const {
    return QStringLiteral("QUpDownButton");
}

QString QUpDownButtonPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / Additional");
}

QIcon QUpDownButtonPlugin::icon() const {
    return QIcon(QStringLiteral(":/qt-project.org/formeditor/images/widgets/toolbutton.png"));
}

QString QUpDownButtonPlugin::toolTip() const {
    return QStringLiteral("A widget that show an up/down (or left/right) pair of button with arrow");
}

QString QUpDownButtonPlugin::whatsThis() const {
    return toolTip();
}

bool QUpDownButtonPlugin::isContainer() const {
    return false;
}

QString QUpDownButtonPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QUpDownButton\" name=\"upDownButton\">\n"
                          "</widget>\n");
}

QString QUpDownButtonPlugin::includeFile() const {
    return QStringLiteral("QUpDownButton.h");
}
