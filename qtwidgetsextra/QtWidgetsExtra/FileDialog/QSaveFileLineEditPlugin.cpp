#include "QSaveFileLineEditPlugin.h"
#include "QSaveFileLineEdit.h"

#include <QApplication>
#include <QStyle>

QSaveFileLineEditPlugin::QSaveFileLineEditPlugin(QObject *parent)
    : QObject(parent)
    , m_initialized(false) {
}

void QSaveFileLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */) {
    if (m_initialized) {
        return;
    }

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QSaveFileLineEditPlugin::isInitialized() const {
    return m_initialized;
}

QWidget *QSaveFileLineEditPlugin::createWidget(QWidget *parent) {
    return new QSaveFileLineEdit(parent);
}

QString QSaveFileLineEditPlugin::name() const {
    return QStringLiteral("QSaveFileLineEdit");
}

QString QSaveFileLineEditPlugin::group() const {
    return QStringLiteral("Qt Widgets Extra / File Dialog");
}

QIcon QSaveFileLineEditPlugin::icon() const {
    return QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton);
}

QString QSaveFileLineEditPlugin::toolTip() const {
    return QStringLiteral("A line edit with a tool button that allow to choose a saving file");
}

QString QSaveFileLineEditPlugin::whatsThis() const {
    return toolTip();
}

bool QSaveFileLineEditPlugin::isContainer() const {
    return false;
}

QString QSaveFileLineEditPlugin::domXml() const {
    return QStringLiteral("<widget class=\"QSaveFileLineEdit\" name=\"saveFileLineEdit\">\n</widget>\n");
}

QString QSaveFileLineEditPlugin::includeFile() const {
    return QStringLiteral("QSaveFileLineEdit.h");
}
