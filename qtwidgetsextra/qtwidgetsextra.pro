TEMPLATE = lib
TARGET = $$qtLibraryTarget(QtWidgetsExtra$${QT_MAJOR_VERSION})
CONFIG *= plugin debug_and_release
DESTDIR = ../bin/designer

greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= designer
} else {
 CONFIG *= designer
}

LIBS *= -L.

DEPENDPATH *= .
INCLUDEPATH *= .

#RESOURCES = qtwidgetsextra.qrc

HEADERS = QtWidgetsExtra.h \
    QEmbedableButton_p.h \
    QOpenFileButtonPlugin.h \
    QOpenFileLineEditPlugin.h \
    QSaveFileButtonPlugin.h \
    QSaveFileLineEditPlugin.h \
    QOpenFolderButtonPlugin.h \
    QOpenFolderLineEditPlugin.h \
    color/QColorPushButtonPlugin.h \
    color/QColorToolButtonPlugin.h

SOURCES = QtWidgetsExtra.cpp \
    QEmbedableButton.cpp \
    QOpenFileButtonPlugin.cpp \
    QOpenFileLineEditPlugin.cpp \
    QSaveFileButtonPlugin.cpp \
    QSaveFileLineEditPlugin.cpp \
    QOpenFolderButtonPlugin.cpp \
    QOpenFolderLineEditPlugin.cpp \
    color/QColorPushButtonPlugin.cpp \
    color/QColorToolButtonPlugin.cpp

include(qopenfile.pri)
include(qsavefile.pri)
include(qopenfolder.pri)
include(color/color.pri)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS *= target
