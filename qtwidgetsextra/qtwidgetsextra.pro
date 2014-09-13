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

include(filedialog/filedialog.pri)
include(color/color.pri)

HEADERS *= QtWidgetsExtra.h \
    QtWidgetsExtraCache.h \
    abstract/QAbstractButtonLineEdit.h \
    abstract/QEmbedableButton_p.h \
    filedialog/QOpenFileButtonPlugin.h \
    filedialog/QOpenFileLineEditPlugin.h \
    filedialog/QSaveFileButtonPlugin.h \
    filedialog/QSaveFileLineEditPlugin.h \
    filedialog/QOpenFolderButtonPlugin.h \
    filedialog/QOpenFolderLineEditPlugin.h \
    color/QColorLineEditPlugin.h \
    color/QColorPushButtonPlugin.h \
    color/QColorToolButtonPlugin.h \
    color/QColorComboBoxPlugin.h

SOURCES *= QtWidgetsExtra.cpp \
    QtWidgetsExtraCache.cpp \
    abstract/QAbstractButtonLineEdit.cpp \
    abstract/QEmbedableButton.cpp \
    filedialog/QOpenFileButtonPlugin.cpp \
    filedialog/QOpenFileLineEditPlugin.cpp \
    filedialog/QSaveFileButtonPlugin.cpp \
    filedialog/QSaveFileLineEditPlugin.cpp \
    filedialog/QOpenFolderButtonPlugin.cpp \
    filedialog/QOpenFolderLineEditPlugin.cpp \
    color/QColorLineEditPlugin.cpp \
    color/QColorPushButtonPlugin.cpp \
    color/QColorToolButtonPlugin.cpp \
    color/QColorComboBoxPlugin.cpp

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS *= target
