add_subdirectory(Light)
add_subdirectory(Mesh)
add_subdirectory(OpenGL)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderGroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderGroup.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer.h
    PARENT_SCOPE
)
