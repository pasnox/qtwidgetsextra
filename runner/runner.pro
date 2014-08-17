TEMPLATE = app
TARGET = $$qtLibraryTarget(QtWidgetsExtraRunner$${QT_MAJOR_VERSION})
CONFIG *= debug_and_release
DESTDIR = ../bin

DEPENDPATH *= .
INCLUDEPATH *= .

DEFINES *= "UI_FILEPATH=\\\"$$PWD/resources/QtWidgetsExtra.ui\\\""

RESOURCES = resources/runner.qrc
SOURCES = main.cpp
