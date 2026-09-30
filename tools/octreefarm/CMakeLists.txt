cmake_minimum_required(VERSION 4.3)

project(octreefarm VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(REQUIRED_QT_VERSION 6.11.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS
    Widgets
)
find_package(Vulkan REQUIRED)

qt_standard_project_setup(
    REQUIRES ${REQUIRED_QT_VERSION}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../../libs)
include_directories(../../trdparty)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)

add_executable(octreefarm
    main.cpp
    Application.cpp Application.h
    MainWindow.cpp MainWindow.h
    Camera.cpp Camera.h
    Command.cpp Command.h
    OctreeEditor.cpp OctreeEditor.h
    Preferences.cpp Preferences.h
    Properties.cpp Properties.h
    RenderEngine.cpp RenderEngine.h
    Source.cpp Source.h Viewport.cpp
    Viewport.h
    config.h
)

target_link_directories(octreefarm PRIVATE $ENV{ORIGIN_HOME})

target_link_libraries(octreefarm PRIVATE
    Qt6::Widgets
    Vulkan::Vulkan
    glm::glm
    octree
    core
)
