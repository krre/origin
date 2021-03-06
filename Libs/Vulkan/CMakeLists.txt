cmake_minimum_required(VERSION 3.5)

project(Vulkan)

set(LIB_NAME "Vulkan")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME}) # For MinGW

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -std=c++17 -fPIC")
endif()

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

add_subdirectory(API)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/GpuBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GpuBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.h
)

add_library(${LIB_NAME} SHARED ${SOURCES})

set(SPIRV_CROSS_LIB $ENV{VULKAN_SDK}/lib/libspirv-cross-core.a)

if(WIN32)
    string(REGEX REPLACE "\\\\" "/" SPIRV_CROSS_LIB ${SPIRV_CROSS_LIB})
else()
    target_link_libraries(${LIB_NAME}
        X11-xcb
    )
endif()

target_link_libraries(${LIB_NAME}
    ${Vulkan_LIBRARIES}
    ${SPIRV_CROSS_LIB} # If linking error, recompile spirv-cross lib with -fPIC flag (on Linux only)
)
