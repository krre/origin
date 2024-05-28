add_subdirectory(light)
add_subdirectory(render)
add_subdirectory(voxel)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Plane.h
    PARENT_SCOPE
)
