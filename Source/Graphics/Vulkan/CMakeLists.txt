add_subdirectory(Wrapper)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanGpuBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanGpuBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderState.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanTexture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanTexture.h
    PARENT_SCOPE
)
