TEMPLATE = lib
TARGET = $$qtLibraryTarget(QtWidgetsExtra$${QT_MAJOR_VERSION})
CONFIG *= plugin debug_and_release

greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= designer
} else {
 CONFIG *= designer
}

LIBS *= -L.

#RESOURCES = qtwidgetsextra.qrc

HEADERS = QtWidgetsExtra.h \
    QOpenFileButtonPlugin.h \
    QOpenFileLineEditPlugin.h \
    QOpenFolderLineEditPlugin.h \
    QEmbedableButton_p.h

SOURCES = QtWidgetsExtra.cpp \
    QOpenFileButtonPlugin.cpp \
    QOpenFileLineEditPlugin.cpp \
    QOpenFolderLineEditPlugin.cpp \
    QEmbedableButton.cpp

include(qopenfile.pri)
include(qopenfolder.pri)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS *= target
