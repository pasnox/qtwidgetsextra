# QtWidgetsExtraRunner Tool

gateau_add_executable(QtWidgetsExtraRunner
    AUTOMOC
    AUTORCC
    PROPERTIES
        RUNTIME_OUTPUT_NAME
            QtWidgetsExtraRunner${QT_VERSION_MAJOR}
    LINK_LIBRARIES
        PUBLIC
            Qt${QT_VERSION_MAJOR}::Core
    SOURCES
        main.cpp
        resources/runner.qrc
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtWidgetsExtraRunner)
endif()
