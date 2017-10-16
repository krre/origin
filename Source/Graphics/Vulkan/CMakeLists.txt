add_subdirectory(Wrapper)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanCore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VulkanCore.h
    PARENT_SCOPE
)
