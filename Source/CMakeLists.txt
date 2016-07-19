add_subdirectory(Core)
add_subdirectory(Debug)
add_subdirectory(Event)
add_subdirectory(ECS)
add_subdirectory(Graphics)
add_subdirectory(Process)
add_subdirectory(Resource)
add_subdirectory(Scene)
add_subdirectory(State)
add_subdirectory(ThirdParty)
add_subdirectory(UI)
add_subdirectory(Universe)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)
