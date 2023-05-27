#include "QFileSystemListViewPlugin.h"
#include "QFileSystemListView.h"

QFileSystemListViewPlugin::QFileSystemListViewPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QFileSystemListViewPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QFileSystemListViewPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QFileSystemListViewPlugin::createWidget(QWidget *parent) {
    return new QFileSystemListView(parent);
}

QString QFileSystemListViewPlugin::name() const {
    return QStringLiteral("QFileSystemListView");
}

QString QFileSystemListViewPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / File System");
}

QIcon QFileSystemListViewPlugin::icon() const {
    return QIcon(QStringLiteral(":/designer/treeview.png"));
}

QString QFileSystemListViewPlugin::toolTip() const {
    return QStringLiteral("A QListView presenting a QFileSystemModel");
}

QString QFileSystemListViewPlugin::whatsThis() const {
    return toolTip();
}

bool QFileSystemListViewPlugin::isContainer() const {
    return false;
}

QString QFileSystemListViewPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QFileSystemListView\" name=\"fileSystemListView\">\n"
                          "</widget>\n");
}

QString QFileSystemListViewPlugin::includeFile() const {
    return QStringLiteral("QFileSystemListView.h");
}
