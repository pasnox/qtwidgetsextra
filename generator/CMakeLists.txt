# QtWidgetsExtraGenerator Tool

gateau_add_executable(QtWidgetsExtraGenerator
    AUTOMOC
    AUTOUIC
    AUTORCC
    PROPERTIES
        RUNTIME_OUTPUT_NAME
            QtWidgetsExtraGenerator${QT_VERSION_MAJOR}
    LINK_LIBRARIES
        PUBLIC
            Qt${QT_VERSION_MAJOR}::Widgets
    HEADERS
        Generator.h
        GeneratorDelegate.h
        MainWindow.h
    SOURCES
        Generator.cpp
        GeneratorDelegate.cpp
        MainWindow.cpp
        MainWindow.ui
        main.cpp
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtWidgetsExtraGenerator)
endif()
