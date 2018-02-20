add_subdirectory(Primitive)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/GPUMemoryManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GPUMemoryManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SVOBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SVOBuilder.h
    PARENT_SCOPE
)
