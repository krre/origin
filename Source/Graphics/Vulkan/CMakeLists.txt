add_subdirectory(Wrapper)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderContext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderWindow.h
    PARENT_SCOPE
)
