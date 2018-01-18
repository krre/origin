add_subdirectory(Wrapper)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanRenderState.h
    PARENT_SCOPE
)
