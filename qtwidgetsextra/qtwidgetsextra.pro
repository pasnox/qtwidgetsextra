TEMPLATE = lib
TARGET = $$qtLibraryTarget(QtWidgetsExtra$${QT_MAJOR_VERSION})
CONFIG *= plugin debug_and_release
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

#RESOURCES = qtwidgetsextra.qrc

HEADERS = QtWidgetsExtra.h \
    QtWidgetsExtraCache.h \
    abstract/QAbstractButtonLineEdit.h \
    QEmbedableButton_p.h \
    QOpenFileButtonPlugin.h \
    QOpenFileLineEditPlugin.h \
    QSaveFileButtonPlugin.h \
    QSaveFileLineEditPlugin.h \
    QOpenFolderButtonPlugin.h \
    QOpenFolderLineEditPlugin.h \
    color/QColorLineEditPlugin.h \
    color/QColorPushButtonPlugin.h \
    color/QColorToolButtonPlugin.h

SOURCES = QtWidgetsExtra.cpp \
    QtWidgetsExtraCache.cpp \
    abstract/QAbstractButtonLineEdit.cpp \
    QEmbedableButton.cpp \
    QOpenFileButtonPlugin.cpp \
    QOpenFileLineEditPlugin.cpp \
    QSaveFileButtonPlugin.cpp \
    QSaveFileLineEditPlugin.cpp \
    QOpenFolderButtonPlugin.cpp \
    QOpenFolderLineEditPlugin.cpp \
    color/QColorLineEditPlugin.cpp \
    color/QColorPushButtonPlugin.cpp \
    color/QColorToolButtonPlugin.cpp

include(qopenfile.pri)
include(qsavefile.pri)
include(qopenfolder.pri)
include(color/color.pri)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS *= target
