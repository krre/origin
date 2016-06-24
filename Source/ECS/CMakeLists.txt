add_subdirectory(Components)
add_subdirectory(Entities)
add_subdirectory(System)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Component.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Family.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Family.h
    ${CMAKE_CURRENT_SOURCE_DIR}/System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/System.h
    PARENT_SCOPE
)
