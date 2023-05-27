#include "QColorPushButtonPlugin.h"
#include "QColorPushButton.h"

QColorPushButtonPlugin::QColorPushButtonPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QColorPushButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QColorPushButtonPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QColorPushButtonPlugin::createWidget(QWidget *parent) {
    return new QColorPushButton(parent);
}

QString QColorPushButtonPlugin::name() const {
    return QStringLiteral("QColorPushButton");
}

QString QColorPushButtonPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / Color");
}

QIcon QColorPushButtonPlugin::icon() const {
    return QIcon(QStringLiteral(":/qt-project.org/formeditor/images/widgets/pushbutton.png"));
}

QString QColorPushButtonPlugin::toolTip() const {
    return QStringLiteral("A push button that present a QColorDialog on click");
}

QString QColorPushButtonPlugin::whatsThis() const {
    return toolTip();
}

bool QColorPushButtonPlugin::isContainer() const {
    return false;
}

QString QColorPushButtonPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QColorPushButton\" name=\"colorPushButton\">\n</widget>\n");
}

QString QColorPushButtonPlugin::includeFile() const {
    return QStringLiteral("QtWidgetsExtra/Color/QColorPushButton.h");
}
