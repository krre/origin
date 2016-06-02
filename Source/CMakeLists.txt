add_subdirectory(Core)
add_subdirectory(Debug)
add_subdirectory(EventManager)
add_subdirectory(Graphics)
add_subdirectory(Process)
add_subdirectory(SceneGraph)
add_subdirectory(UI)
add_subdirectory(World)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)
