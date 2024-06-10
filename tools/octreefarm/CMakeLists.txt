cmake_minimum_required(VERSION 3.22)

project(octreefarm VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
)

qt_standard_project_setup()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../../libs)
include_directories(../../trdparty)

add_executable(octreefarm
    main.cpp
    Application.cpp Application.h
    MainWindow.cpp MainWindow.h
    Camera.cpp Camera.h
    Command.cpp Command.h
    OctreeEditor.cpp OctreeEditor.h
    Options.cpp Options.h
    Properties.cpp Properties.h
    RenderEngine.cpp RenderEngine.h
    Source.cpp Source.h Viewport.cpp
    Viewport.h
    config.h
)

target_link_directories(octreefarm PRIVATE $ENV{ORIGIN_HOME})

target_link_libraries(octreefarm PRIVATE
    Qt6::Widgets
    vulkan-o
    octree
    core
)
