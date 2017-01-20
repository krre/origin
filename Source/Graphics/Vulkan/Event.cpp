#include "Event.h"

using namespace Vulkan;

Event::Event(const Device* device) : device(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
}

Event::~Event() {
    vkDestroyEvent(device->getHandle(), handle, nullptr);
}

VkResult Event::create() {
    return checkError(vkCreateEvent(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create event");
}
