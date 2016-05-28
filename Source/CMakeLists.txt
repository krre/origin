add_subdirectory(Core)
add_subdirectory(UI)
add_subdirectory(EventManager)
add_subdirectory(Graphics3D)
add_subdirectory(Process)
add_subdirectory(Debug)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)
