add_subdirectory(Primitive)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Octree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Octree.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OctreeRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/OctreeRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderSurface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderSurface.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel.h
    PARENT_SCOPE
)
