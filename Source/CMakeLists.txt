add_subdirectory(Component)
add_subdirectory(Core)
add_subdirectory(Debug)
add_subdirectory(Event)
add_subdirectory(Entity)
add_subdirectory(Graphics)
add_subdirectory(Process)
add_subdirectory(Scene)
add_subdirectory(System)
add_subdirectory(UI)
add_subdirectory(World)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)
