#include "Event.h"

namespace Vulkan {

Event::Event(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
}

Event::~Event() {
    vkDestroyEvent(device->getHandle(), handle, nullptr);
}

void Event::create() {
    VULKAN_CHECK_RESULT(vkCreateEvent(device->getHandle(), &createInfo, nullptr, &handle), "Failed to create event");
}

} // Vulkan
