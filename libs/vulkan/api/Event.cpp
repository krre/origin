#include "Event.h"

namespace Vulkan {

Event::Event(Device* device) : Devicer(device) {
    createInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
}

Event::~Event() {
    vkDestroyEvent(m_device->handle(), m_handle, nullptr);
}

void Event::create() {
    VULKAN_CHECK_RESULT(vkCreateEvent(m_device->handle(), &createInfo, nullptr, &m_handle), "Failed to create event");
}

}
