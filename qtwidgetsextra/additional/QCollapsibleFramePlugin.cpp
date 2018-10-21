#include "QCollapsibleFramePlugin.h"
#include "QCollapsibleFrame.h"

#include <QtPlugin>

QCollapsibleFramePlugin::QCollapsibleFramePlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
{
}

void QCollapsibleFramePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QCollapsibleFramePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QCollapsibleFramePlugin::createWidget(QWidget *parent)
{
    return new QCollapsibleFrame(parent);
}

QString QCollapsibleFramePlugin::name() const
{
    return QLatin1String("QCollapsibleFrame");
}

QString QCollapsibleFramePlugin::group() const
{
    return QLatin1String("Qt Widgets Extra / Additional");
}

QIcon QCollapsibleFramePlugin::icon() const
{
    return QIcon(QLatin1String(":/qt-project.org/formeditor/images/widgets/frame.png"));
}

QString QCollapsibleFramePlugin::toolTip() const
{
    return QLatin1String("A widget that can shrink and grow using a collapse button");
}

QString QCollapsibleFramePlugin::whatsThis() const
{
    return toolTip();
}

bool QCollapsibleFramePlugin::isContainer() const
{
    return true;
}

QString QCollapsibleFramePlugin::domXml() const
{
    return QLatin1String(
        "<widget class=\"QCollapsibleFrame\" name=\"collapsibleFrame\">\n"
        "</widget>\n"
    );
}

QString QCollapsibleFramePlugin::includeFile() const
{
    return QLatin1String("QCollapsibleFrame.h");
}
