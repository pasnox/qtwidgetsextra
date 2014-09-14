TEMPLATE = lib
TARGET = $$qtLibraryTarget(QtWidgetsExtra$${QT_MAJOR_VERSION})
CONFIG *= plugin
DESTDIR = ../bin/designer

greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= designer
} else {
 CONFIG *= designer
}

# Disable some implicit cast to avoid convertion errors
DEFINES *= \
    QT_NO_URL_CAST_FROM_STRING \
    QT_NO_CAST_TO_ASCII \
    QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_FROM_BYTEARRAY

LIBS *= -L.

DEPENDPATH *= . \
    abstract

INCLUDEPATH *= . \
    abstract

#RESOURCES *= qtwidgetsextra.qrc

HEADERS *= QtWidgetsExtra.h \
    QtWidgetsExtraCache.h \
    abstract/QAbstractButtonLineEdit.h \
    abstract/QEmbedableButton_p.h

SOURCES *= QtWidgetsExtra.cpp \
    QtWidgetsExtraCache.cpp \
    abstract/QAbstractButtonLineEdit.cpp \
    abstract/QEmbedableButton.cpp

# Auto discovering stuffs
GEN_PLUGINS_HEADERS = generated/pluginsHeaders.h
GEN_PLUGINS_NEW = generated/pluginsNew.h

# Cleanup, using $$ on system is required so in QtCreator parser do execute the system call...
win32 {
    !exists($$dirname(GEN_PLUGINS_HEADERS)):Z = $$system(mkdir $$dirname(GEN_PLUGINS_HEADERS))
    exists($${GEN_PLUGINS_HEADERS}):Z = $$system(del $${GEN_PLUGINS_HEADERS})
    exists($${GEN_PLUGINS_NEW}):Z = $$system(del $${GEN_PLUGINS_NEW})
} else {
    !exists($$dirname(GEN_PLUGINS_HEADERS)):Z = $$system(mkdir -p $$dirname(GEN_PLUGINS_HEADERS))
    exists($${GEN_PLUGINS_HEADERS}):Z = $$system(rm ./$${GEN_PLUGINS_HEADERS})
    exists($${GEN_PLUGINS_NEW}):Z = $$system(rm ./$${GEN_PLUGINS_NEW})
}

# Auto discover project include files
projectFiles = $$files(*.pri, true)
for(projectFile, projectFiles) {
    include($${projectFile})
}

# Auto discovered plugins classes
sourceFiles = $$files(*Plugin.*, true)
for(sourceFile, sourceFiles) {
    sourceFileSuffix = $$section(sourceFile, ., -1)
    isEqual(sourceFileSuffix, cpp):SOURCES *= $${sourceFile}
    isEqual(sourceFileSuffix, h) {
        HEADERS *= $${sourceFile}
        # Using $$ on system is required so in QtCreator parser do execute the system call...
        baseName = $$basename(sourceFile)
        Z = $$system(echo \"$${LITERAL_HASH}include \\\"$${baseName}\\\"\" >> $${GEN_PLUGINS_HEADERS})
        Z = $$system(echo \"m_widgets.append(new $$section(baseName, ., 0, 0)(this));\" >> $${GEN_PLUGINS_NEW})
    }
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS *= target
