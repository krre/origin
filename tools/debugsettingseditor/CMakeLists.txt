cmake_minimum_required(VERSION 3.22)

project(dse VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
)

qt_standard_project_setup()

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(../../libs)

add_executable(dse
    main.cpp
    Application.cpp Application.h
    MainWindow.cpp MainWindow.h
    AbstractTab.h
    GeneralTab.cpp GeneralTab.h
    ListBox.cpp ListBox.h
    SelectButtonRow.cpp SelectButtonRow.h
    VulkanTab.cpp VulkanTab.h
)

target_link_directories(dse PRIVATE $ENV{ORIGIN_HOME})

target_link_libraries(dse PRIVATE
    Qt6::Widgets
    vulkan-o
)
