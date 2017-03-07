cmake_minimum_required(VERSION 3.5)

project(origin)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

configure_file(Origin.h.in Origin.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Source)
add_subdirectory(ThirdParty)

set(EXECUTABLE_NAME "origin")
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_range_for)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# If find SDL2 failure, set SDL_PATH variable to SDL install root
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})

include_directories(ThirdParty)

target_link_libraries(${EXECUTABLE_NAME}
    ${SDL2_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${BULLET_LIBRARIES}
    stdc++fs)

IF (WIN32)
    find_package(Vulkan REQUIRED)

    include_directories(${Vulkan_INCLUDE_DIRS})
    include_directories($ENV{VULKAN_SDK}/spirv-tools/include)

    SET(SPIRV_TOOLS_LIB $ENV{VULKAN_SDK}/lib32/libSPIRV-Tools.a)
    STRING(REGEX REPLACE "\\\\" "/" SPIRV_TOOLS_LIB ${SPIRV_TOOLS_LIB})

    target_link_libraries(${EXECUTABLE_NAME}
        ${Vulkan_LIBRARIES}
        ${SPIRV_TOOLS_LIB})
ELSE()
    include_directories($ENV{VULKAN_SDK}/include)

    target_link_libraries(${EXECUTABLE_NAME}
        $ENV{VULKAN_SDK}/lib/libvulkan.so
        $ENV{VULKAN_SDK}/lib/spirv-tools/libSPIRV-Tools.a
        X11-xcb)
ENDIF()

# Show in QtCreator project tree
FILE(GLOB_RECURSE Markdown "*.md")
FILE(GLOB_RECURSE Data "Data/*.*")
FILE(GLOB_RECURSE Debug "Debug/*.*")
add_custom_target(markdown SOURCES ${Markdown})
add_custom_target(data SOURCES ${Data})
add_custom_target(debug SOURCES ${Debug})
