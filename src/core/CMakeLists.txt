add_subdirectory(screens)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp
    PARENT_SCOPE
)
