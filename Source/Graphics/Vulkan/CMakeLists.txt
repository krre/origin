add_subdirectory(Wrapper)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanCore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanCore.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderWindow.h
    PARENT_SCOPE
)
