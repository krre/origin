#include "Event.h"

using namespace Vulkan;

Event::Event(const Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
}

Event::~Event() {
    vkDestroyEvent(device->getHandle(), handle, nullptr);
}

VkResult Event::create() {
    CHECK_RESULT(vkCreateEvent(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create event");
}
