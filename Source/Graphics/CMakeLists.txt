add_subdirectory(Buffer)
add_subdirectory(Light)
add_subdirectory(Render)
add_subdirectory(Voxel)

if(VULKAN_BACKEND)
    add_subdirectory(Vulkan)
    message("Vulkan backend enabled")
else()
    message("Vulkan backend disabled")
endif()

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsTypes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mesh.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Plane.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Texture.h
    PARENT_SCOPE
)
