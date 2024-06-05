set(LIB_NAME "vulkan-o")

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

add_library(${LIB_NAME} SHARED
    GpuBuffer.cpp GpuBuffer.h
    Renderer.cpp Renderer.h
    Shader.cpp Shader.h
    ShaderProgram.cpp ShaderProgram.h
    Texture.cpp Texture.h
    api/DebugReportCallback.cpp api/DebugReportCallback.h
    api/Event.cpp api/Event.h
    api/Fence.cpp api/Fence.h
    api/Framebuffer.cpp api/Framebuffer.h
    api/Instance.cpp api/Instance.h
    api/QueryPool.cpp api/QueryPool.h
    api/Queue.cpp api/Queue.h
    api/RenderPass.cpp api/RenderPass.h
    api/Sampler.cpp api/Sampler.h
    api/Semaphore.cpp api/Semaphore.h
    api/ShaderModule.cpp api/ShaderModule.h
    api/base/Collection.h
    api/base/Handle.h api/base/Handle.cpp
    api/buffer/Buffer.cpp api/buffer/Buffer.h
    api/buffer/BufferView.cpp api/buffer/BufferView.h
    api/command/CommandBuffers.cpp api/command/CommandBuffers.h
    api/command/CommandBuffer.cpp api/command/CommandBuffer.h
    api/command/CommandBufferOneTime.cpp api/command/CommandBufferOneTime.h
    api/command/CommandPool.cpp api/command/CommandPool.h
    api/descriptor/DescriptorPool.cpp api/descriptor/DescriptorPool.h
    api/descriptor/DescriptorSets.cpp api/descriptor/DescriptorSets.h
    api/descriptor/DescriptorSetLayout.cpp api/descriptor/DescriptorSetLayout.h
    api/device/Device.cpp api/device/Device.h
    api/device/DeviceMemory.cpp api/device/DeviceMemory.h
    api/device/Devicer.cpp api/device/Devicer.h
    api/device/PhysicalDevice.cpp api/device/PhysicalDevice.h
    api/device/PhysicalDevices.cpp api/device/PhysicalDevices.h
    api/image/Image.cpp api/image/Image.h
    api/image/ImageView.cpp api/image/ImageView.h
    api/pipeline/ComputePipeline.cpp api/pipeline/ComputePipeline.h
    api/pipeline/GraphicsPipeline.cpp api/pipeline/GraphicsPipeline.h
    api/pipeline/PipelineCache.cpp api/pipeline/PipelineCache.h
    api/pipeline/Pipeline.cpp api/pipeline/Pipeline.h
    api/pipeline/PipelineLayout.cpp api/pipeline/PipelineLayout.h
    api/surface/Surface.cpp api/surface/Surface.h
    api/surface/Swapchain.cpp api/surface/Swapchain.h
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
