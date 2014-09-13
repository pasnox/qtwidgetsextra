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

# Auto discover project include files
projectFiles = $$files(*.pri, true)
for(projectFile, projectFiles) {
    include($$projectFile)
}

# Auto discovered plugins classes
sourceFiles = $$files(*Plugin.*, true)
for(sourceFile, sourceFiles) {
    sourceFileSuffix = $$section(sourceFile, ., -1)
    isEqual(sourceFileSuffix, h):HEADERS *= $$sourceFile
    isEqual(sourceFileSuffix, cpp):SOURCES *= $$sourceFile
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS *= target
