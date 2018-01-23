cmake_minimum_required(VERSION 3.5)

project(VulkanRenderer)

set(LIB_NAME "VulkanRenderer")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{ORIGIN_HOME})

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

add_subdirectory(API)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/GpuBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GpuBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.h
)

add_library(${LIB_NAME} SHARED ${SOURCES})

if(WIN32)
    include_directories($ENV{VULKAN_SDK}/spirv-tools/include)

    set(SPIRV_TOOLS_LIB $ENV{VULKAN_SDK}/lib32/libSPIRV-Tools.a)
    string(REGEX REPLACE "\\\\" "/" SPIRV_TOOLS_LIB ${SPIRV_TOOLS_LIB})

    target_link_libraries(${LIB_NAME}
        ${SPIRV_TOOLS_LIB}
    )
else()
    target_link_libraries(${LIB_NAME}
        $ENV{VULKAN_SDK}/lib/spirv-tools/libSPIRV-Tools.a
        X11-xcb
    )
endif()

target_link_libraries(${LIB_NAME}
    ${Vulkan_LIBRARIES}
)
