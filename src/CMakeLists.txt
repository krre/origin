add_subdirectory(base)
add_subdirectory(debug)
add_subdirectory(ecs)
add_subdirectory(event)
add_subdirectory(graphics)
add_subdirectory(process)
add_subdirectory(resource)
add_subdirectory(screen)
add_subdirectory(ui)
add_subdirectory(world)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)
