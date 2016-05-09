cmake_minimum_required(VERSION 3.5)

project(gagarin)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

add_subdirectory(src)

add_executable(gagarin ${MAIN_SOURCES})
target_compile_features(gagarin PRIVATE cxx_range_for)

target_link_libraries (gagarin SDL2main SDL2)
