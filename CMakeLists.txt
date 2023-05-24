cmake_minimum_required(VERSION 3.15.0)

project(QtWidgetsExtra
    VERSION 0.1
    DESCRIPTION "QtWidgetsExtra is a library that extends Qt Designer Widgets palette."
    HOMEPAGE_URL "https://github.com/pasnox/qtwidgetsextra"
    LANGUAGES C CXX
)

# Include Gateau by fetching it. One may also use it as a submodule
include(FetchContent)
FetchContent_Declare(gateau GIT_REPOSITORY https://github.com/palacaze/gateau.git)
FetchContent_MakeAvailable(gateau)
include(${gateau_SOURCE_DIR}/Gateau.cmake)

# Include Gateau by using a local copy
#include(3rdparty/gateau/Gateau.cmake)

option(QT_WIDGETS_EXTRA_BUILD_GENERATOR "Build the generator tool" OFF)
option(QT_WIDGETS_EXTRA_BUILD_DESIGNER "Build the designer plugin" OFF)
option(QT_WIDGETS_EXTRA_BUILD_RUNNER "Build the runner tool" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX d)

# Configure gateau for this project
gateau_configure(
    C_STANDARD c_std_99
    CXX_STANDARD cxx_std_17
    EXTERNAL_ROOT "${PROJECT_BINARY_DIR}/3rdParty"
    OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    GENERATED_HEADER_CASE CAMEL
    GENERATED_HEADER_EXT h
    #NAMESPACE Qt
    #NAME_PREFIX Qt
)

if (QT_WIDGETS_EXTRA_BUILD_DESIGNER)
    set(DESIGNER_LIB "Designer")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test ${DESIGNER_LIB})
gateau_find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Test ${DESIGNER_LIB})

gateau_other_files(Others
    TODO.md
    README.md
    LICENSE.md
    .clang-format
    .gitignore
)

if (QT_WIDGETS_EXTRA_BUILD_GENERATOR)
    add_subdirectory(generator)
endif()
add_subdirectory(qtwidgetsextra)
if (QT_WIDGETS_EXTRA_BUILD_RUNNER)
    add_subdirectory(runner)
endif()

# Examples
if (QT_WIDGETS_EXTRA_BUILD_EXAMPLES)
    # add_subdirectory(example)
endif()

# Tests
if (QT_WIDGETS_EXTRA_BUILD_TESTS)
    enable_testing()
    #add_subdirectory(test)
endif()

# Documentation
if (QT_WIDGETS_EXTRA_BUILD_DOC)
    # gateau_build_documentation(
    #     EXCLUDED_SYMBOLS
    #         detail  # exclude "detail" namespace
    #         _*      # and symbols starting with a "_"
    # )
endif()

gateau_install_project()
