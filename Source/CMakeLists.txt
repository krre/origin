add_subdirectory(Core)
add_subdirectory(UI)
add_subdirectory(EventManager)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
)
