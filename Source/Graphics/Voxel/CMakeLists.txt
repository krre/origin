add_subdirectory(Primitive)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Octree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Octree.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderSurface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderSurface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SVOBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SVOBuilder.h
    PARENT_SCOPE
)
