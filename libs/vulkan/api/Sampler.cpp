#include "Sampler.h"

namespace Vulkan {

Sampler::Sampler(Device* device) : Devicer(device) {
    m_createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    m_createInfo.magFilter = VK_FILTER_NEAREST;
    m_createInfo.minFilter = VK_FILTER_NEAREST;
    m_createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    m_createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    m_createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    m_createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    m_createInfo.mipLodBias = 0.0f;
    m_createInfo.compareOp = VK_COMPARE_OP_NEVER;
    m_createInfo.minLod = 0.0f;
    m_createInfo.maxLod = 1.0f;
    m_createInfo.maxAnisotropy = 1.0;
    m_createInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
}

Sampler::~Sampler() {
    vkDestroySampler(m_device->handle(), m_handle, nullptr);
}

void Sampler::create() {
    VULKAN_CHECK_RESULT(vkCreateSampler(m_device->handle(), &m_createInfo, nullptr, &m_handle), "Failed to create sampler");
}

}
