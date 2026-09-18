cmake_minimum_required(VERSION 4.3)

project(assemblybox VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(REQUIRED_QT_VERSION 6.11.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS
    Widgets
)

qt_standard_project_setup(
    REQUIRES ${REQUIRED_QT_VERSION}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(assemblybox
    main.cpp
    Application.cpp Application.h
    MainWindow.cpp MainWindow.h
)

target_link_libraries(assemblybox PRIVATE
    Qt6::Widgets
)
