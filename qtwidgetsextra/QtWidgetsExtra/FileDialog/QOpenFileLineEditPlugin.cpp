#include "QOpenFileLineEditPlugin.h"
#include "QOpenFileLineEdit.h"

#include <QApplication>
#include <QStyle>

QOpenFileLineEditPlugin::QOpenFileLineEditPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QOpenFileLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QOpenFileLineEditPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QOpenFileLineEditPlugin::createWidget(QWidget *parent) {
    return new QOpenFileLineEdit(parent);
}

QString QOpenFileLineEditPlugin::name() const {
    return QStringLiteral("QOpenFileLineEdit");
}

QString QOpenFileLineEditPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / File Dialog");
}

QIcon QOpenFileLineEditPlugin::icon() const {
    return QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton);
}

QString QOpenFileLineEditPlugin::toolTip() const {
    return QStringLiteral("A line edit with a tool button that allow to choose an opening file");
}

QString QOpenFileLineEditPlugin::whatsThis() const {
    return toolTip();
}

bool QOpenFileLineEditPlugin::isContainer() const {
    return false;
}

QString QOpenFileLineEditPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QOpenFileLineEdit\" name=\"openFileLineEdit\">\n</widget>\n");
}

QString QOpenFileLineEditPlugin::includeFile() const {
    return QStringLiteral("QtWidgetsExtra/FileDialog/QOpenFileLineEdit.h");
}
