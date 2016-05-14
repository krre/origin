cmake_minimum_required(VERSION 3.5)

project(gagarin)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

add_subdirectory(src)

set(EXECUTABLE_NAME "gagarin")
add_executable(${EXECUTABLE_NAME} ${MAIN_SOURCES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_range_for)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS system window graphics network audio)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
