#include "QColorListViewPlugin.h"
#include "QColorListView.h"

QColorListViewPlugin::QColorListViewPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QColorListViewPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QColorListViewPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QColorListViewPlugin::createWidget(QWidget *parent) {
    return new QColorListView(parent);
}

QString QColorListViewPlugin::name() const {
    return QStringLiteral("QColorListView");
}

QString QColorListViewPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / Color");
}

QIcon QColorListViewPlugin::icon() const {
    return QIcon(QStringLiteral(":/qt-project.org/formeditor/images/widgets/listbox.png"));
}

QString QColorListViewPlugin::toolTip() const {
    return QStringLiteral("A list view that present a QColorListModel");
}

QString QColorListViewPlugin::whatsThis() const {
    return toolTip();
}

bool QColorListViewPlugin::isContainer() const {
    return false;
}

QString QColorListViewPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QColorListView\" name=\"colorListView\">\n"
                          "<property name=\"colorNames\">\n"
                          "<stringlist>\n"
                          "<string>#ff0000</string>\n"
                          "<string>#00ff00</string>\n"
                          "<string>#0000ff</string>\n"
                          "</stringlist>\n"
                          "</property>\n"
                          "</widget>\n");
}

QString QColorListViewPlugin::includeFile() const {
    return QStringLiteral("QColorListView.h");
}
