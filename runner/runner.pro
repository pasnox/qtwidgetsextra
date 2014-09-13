TEMPLATE = app
TARGET = $$qtLibraryTarget(QtWidgetsExtraRunner$${QT_MAJOR_VERSION})
DESTDIR = ../bin

# Disable some implicit cast to avoid convertion errors
DEFINES *= \
    QT_NO_URL_CAST_FROM_STRING \
    QT_NO_CAST_TO_ASCII \
    QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_FROM_BYTEARRAY

DEPENDPATH *= .
INCLUDEPATH *= .

DEFINES *= "UI_FILEPATH=\\\"$$PWD/resources/QtWidgetsExtra.ui\\\""

RESOURCES = resources/runner.qrc
SOURCES = main.cpp
