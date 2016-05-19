add_subdirectory(screens)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
    PARENT_SCOPE
)
