#include "QFileSystemListViewPlugin.h"
#include "QFileSystemListView.h"

#include <QtPlugin>

QFileSystemListViewPlugin::QFileSystemListViewPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
}

void QFileSystemListViewPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QFileSystemListViewPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QFileSystemListViewPlugin::createWidget(QWidget *parent)
{
    return new QFileSystemListView(parent);
}

QString QFileSystemListViewPlugin::name() const
{
    return QLatin1String("QFileSystemListView");
}

QString QFileSystemListViewPlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / File System");
}

QIcon QFileSystemListViewPlugin::icon() const
{
    return QIcon(QLatin1String(":/designer/treeview.png"));
}

QString QFileSystemListViewPlugin::toolTip() const
{
    return QLatin1String("A QListView presenting a QFileSystemModel");
}

QString QFileSystemListViewPlugin::whatsThis() const
{
    return toolTip();
}

bool QFileSystemListViewPlugin::isContainer() const
{
    return false;
}

QString QFileSystemListViewPlugin::domXml() const
{
    return QLatin1String(
        "<widget class=\"QFileSystemListView\" name=\"filesystemListView\">\n"
        "</widget>\n"
    );
}

QString QFileSystemListViewPlugin::includeFile() const
{
    return QLatin1String("QFileSystemListView.h");
}
