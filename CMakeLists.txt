cmake_minimum_required(VERSION 3.5)

project(Origin)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(NAME_STRING ${PROJECT_NAME})
set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(STATUS_STRING "Preview Alpha")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(${PROJECT_NAME}.h.in ${PROJECT_NAME}.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Libs)
add_subdirectory(Source)
add_subdirectory(ThirdParty)

set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# If find SDL2 failure, set SDL_PATH variable to SDL install root
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

include_directories(Source)
include_directories(ThirdParty)
include_directories(Libs)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME}
    ${SDL2_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${BULLET_LIBRARIES}
    stdc++fs
    Core
    Vulkan
    Octree
)

if(UNIX)
    target_link_libraries(${EXECUTABLE_NAME}
        png
        z # zlib
    )
endif()

# Show in QtCreator project tree
file(GLOB_RECURSE Root "*.md" "*.in" "Data/*.*" "Debug/*.*" "Source/Template/*.*" "Libs/*.*")
add_custom_target(root SOURCES ${Root})
