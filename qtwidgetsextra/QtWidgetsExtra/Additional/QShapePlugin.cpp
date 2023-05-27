#include "QShapePlugin.h"
#include "QShape.h"

QShapePlugin::QShapePlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QShapePlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QShapePlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QShapePlugin::createWidget(QWidget *parent) {
    return new QShape(parent);
}

QString QShapePlugin::name() const {
    return QStringLiteral("QShape");
}

QString QShapePlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / Additional");
}

QIcon QShapePlugin::icon() const {
    return QIcon(QStringLiteral(":/qt-project.org/formeditor/images/widgets/graphicsview.png"));
}

QString QShapePlugin::toolTip() const {
    return QStringLiteral("A widget that draw some defined or custom paths");
}

QString QShapePlugin::whatsThis() const {
    return toolTip();
}

bool QShapePlugin::isContainer() const {
    return false;
}

QString QShapePlugin::domXml() const {
    return QStringLiteral("<widget class=\"QShape\" name=\"shape\">\n"
                          "</widget>\n");
}

QString QShapePlugin::includeFile() const {
    return QStringLiteral("QShape.h");
}
