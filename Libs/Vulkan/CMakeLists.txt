set(LIB_NAME "Vulkan")

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

add_subdirectory(API)

add_library(${LIB_NAME} SHARED
    ${SOURCES}
    GpuBuffer.cpp GpuBuffer.h
    Renderer.cpp Renderer.h
    Shader.cpp Shader.h
    ShaderProgram.cpp ShaderProgram.h
    Texture.cpp Texture.h
)

set(SPIRV_CROSS_LIB $ENV{VULKAN_SDK}/lib/libspirv-cross-core.a)

if(WIN32)
    string(REGEX REPLACE "\\\\" "/" SPIRV_CROSS_LIB ${SPIRV_CROSS_LIB})
else()
    target_link_libraries(${LIB_NAME}
        X11-xcb
    )
endif()

target_link_libraries(${LIB_NAME}
    ${Vulkan_LIBRARIES}
    ${SPIRV_CROSS_LIB} # If linking error, recompile spirv-cross lib with -fPIC flag (on Linux only)
)
