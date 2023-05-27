#include "QFileSystemTreeViewPlugin.h"
#include "QFileSystemTreeView.h"

QFileSystemTreeViewPlugin::QFileSystemTreeViewPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QFileSystemTreeViewPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QFileSystemTreeViewPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QFileSystemTreeViewPlugin::createWidget(QWidget *parent) {
    return new QFileSystemTreeView(parent);
}

QString QFileSystemTreeViewPlugin::name() const {
    return QStringLiteral("QFileSystemTreeView");
}

QString QFileSystemTreeViewPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / File System");
}

QIcon QFileSystemTreeViewPlugin::icon() const {
    return QIcon(QStringLiteral(":/designer/listview.png"));
}

QString QFileSystemTreeViewPlugin::toolTip() const {
    return QStringLiteral("A QTreeView presenting a QFileSystemModel");
}

QString QFileSystemTreeViewPlugin::whatsThis() const {
    return toolTip();
}

bool QFileSystemTreeViewPlugin::isContainer() const {
    return false;
}

QString QFileSystemTreeViewPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QFileSystemTreeView\" name=\"filesystemTreeView\">\n"
                          "</widget>\n");
}

QString QFileSystemTreeViewPlugin::includeFile() const {
    return QStringLiteral("QFileSystemTreeView.h");
}
