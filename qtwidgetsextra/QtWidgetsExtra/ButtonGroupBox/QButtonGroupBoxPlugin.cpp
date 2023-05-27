#include "QButtonGroupBoxPlugin.h"
#include "QButtonGroupBox.h"

QButtonGroupBoxPlugin::QButtonGroupBoxPlugin(QObject *parent)
    : QObject(parent) {
    m_initialized = false;
}

void QButtonGroupBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QButtonGroupBoxPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QButtonGroupBoxPlugin::createWidget(QWidget *parent) {
    return new QButtonGroupBox(parent);
}

QString QButtonGroupBoxPlugin::name() const {
    return QStringLiteral("QButtonGroupBox");
}

QString QButtonGroupBoxPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / Group Box");
}

QIcon QButtonGroupBoxPlugin::icon() const {
    return QIcon(QStringLiteral(":/qt-project.org/formeditor/images/widgets/groupbox.png"));
}

QString QButtonGroupBoxPlugin::toolTip() const {
    return QStringLiteral("A widget to manage multiple checkable buttons");
}

QString QButtonGroupBoxPlugin::whatsThis() const {
    return toolTip();
}

bool QButtonGroupBoxPlugin::isContainer() const {
    return false;
}

QString QButtonGroupBoxPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QButtonGroupBox\" name=\"buttonGroupBox\">\n</widget>\n");
}

QString QButtonGroupBoxPlugin::includeFile() const {
    return QStringLiteral("QtWidgetsExtra/ButtonGroupBox/QButtonGroupBox.h");
}
