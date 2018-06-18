cmake_minimum_required(VERSION 3.5)

project(Octree)

set(LIB_NAME "Octree")
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

include_directories(../../ThirdParty)
include_directories(../../Libs)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/JsonStorage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/JsonStorage.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Octree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Octree.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Substance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Substance.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SubstanceTree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SubstanceTree.h
)

add_library(${LIB_NAME} SHARED ${SOURCES})

target_link_libraries(${LIB_NAME}
    Core
)
