cmake_minimum_required(VERSION 3.5)

project(origin)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(Origin.h.in Origin.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Source)
add_subdirectory(ThirdParty)

set(EXECUTABLE_NAME "origin")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# If find SDL2 failure, set SDL_PATH variable to SDL install root
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})

if(WIN32)
    find_package(Vulkan REQUIRED)

    include_directories(${Vulkan_INCLUDE_DIRS})
    include_directories($ENV{VULKAN_SDK}/spirv-tools/include)

    set(SPIRV_TOOLS_LIB $ENV{VULKAN_SDK}/lib32/libSPIRV-Tools.a)
    string(REGEX REPLACE "\\\\" "/" SPIRV_TOOLS_LIB ${SPIRV_TOOLS_LIB})

    target_link_libraries(${EXECUTABLE_NAME}
        ${Vulkan_LIBRARIES}
        ${SPIRV_TOOLS_LIB}
    )
else()
    include_directories($ENV{VULKAN_SDK}/include)

    target_link_libraries(${EXECUTABLE_NAME}
        $ENV{VULKAN_SDK}/lib/libvulkan.so
        $ENV{VULKAN_SDK}/lib/spirv-tools/libSPIRV-Tools.a
        X11-xcb
    )
endif()

include_directories(Source)
include_directories(ThirdParty)

target_link_libraries(${EXECUTABLE_NAME}
    ${SDL2_LIBRARY}
    ${BULLET_LIBRARIES}
    stdc++fs
)

# Show in QtCreator project tree
file(GLOB_RECURSE Root "*.md" "*.in" "Data/*.*" "Debug/*.*")
add_custom_target(root SOURCES ${Root})
