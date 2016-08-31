add_subdirectory(Light)
add_subdirectory(OpenGL)
add_subdirectory(Voxel)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.h
    PARENT_SCOPE
)
