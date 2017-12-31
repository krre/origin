add_subdirectory(Wrapper)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanContext.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderWindow.h
    PARENT_SCOPE
)
