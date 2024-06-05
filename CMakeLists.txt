cmake_minimum_required(VERSION 3.22)

project(origin VERSION 0.1.0)

set(STATUS "Preview Alpha")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(trdparty)

set(EXECUTABLE_NAME ${PROJECT_NAME})

# If find SDL2 failure, set SDL_PATH variable to SDL install root
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

include_directories(src)
include_directories(trdparty)
include_directories(libs)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME}
    ${SDL2_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${BULLET_LIBRARIES}
    stdc++fs
    core
    vulkan-o
    octree
)

if(UNIX)
    target_link_libraries(${EXECUTABLE_NAME}
        png
        z # zlib
    )
endif()

# Show in QtCreator project tree
file(GLOB_RECURSE Root "*.md" "*.in" "data/*.*" "debug/*.*")
add_custom_target(root SOURCES ${Root})
