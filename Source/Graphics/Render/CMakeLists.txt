if(ENABLE_OPENGL)
    add_subdirectory(OpenGL)
endif()

if(ENABLE_VULKAN)
    add_subdirectory(Vulkan)
endif()

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RendererSet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RendererSet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderTarget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderTarget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderWindow.h
    PARENT_SCOPE
)
