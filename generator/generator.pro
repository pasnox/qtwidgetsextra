TEMPLATE = app
TARGET = $$qtLibraryTarget(QtWidgetsExtraGenerator$${QT_MAJOR_VERSION})
greaterThan(QT_MAJOR_VERSION, 4):QT *= widgets
DESTDIR = ../bin

DEPENDPATH *= .
INCLUDEPATH *= .

FORMS *= \
    MainWindow.ui

HEADERS *= \
    MainWindow.h \
    GeneratorDelegate.h \
    Generator.h

SOURCES *= main.cpp \
    MainWindow.cpp \
    GeneratorDelegate.cpp \
    Generator.cpp
