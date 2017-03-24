#include "CommandBuffers.h"
#include <assert.h>

using namespace Vulkan;

CommandBuffers::CommandBuffers(const Device* device, const CommandPool* commandPool, VkCommandBufferLevel level) :
    Devicer(device), commandPool(commandPool) {
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = level;
    allocateInfo.commandPool = commandPool->getHandle();
}

CommandBuffers::~CommandBuffers() {
    destroy();
}

bool CommandBuffers::allocate(uint32_t count) {
    assert(collection.size() == 0 && count > 0);
    collection.resize(count);
    allocateInfo.commandBufferCount = count;

    CHECK_RESULT(vkAllocateCommandBuffers(device->getHandle(), &allocateInfo, collection.data()), "Failed to allocate command buffers");
}

void CommandBuffers::destroy() {
    VULKAN_DESTROY_COLLECTION(vkFreeCommandBuffers(device->getHandle(), commandPool->getHandle(), collection.size(), collection.data()));
}
