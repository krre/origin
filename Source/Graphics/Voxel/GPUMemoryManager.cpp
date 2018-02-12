#include "GPUMemoryManager.h"
#include "Resource/ResourceManager.h"
#include "ECS/Components/Components.h"
#include "ECS/Entity.h"
#include "VulkanRenderer/API/Buffer/Buffer.h"

namespace Origin {

GPUMemoryManager::GPUMemoryManager() {
}

void GPUMemoryManager::addEntity(Entity* entity, Vulkan::Buffer* buffer) {
    OctreeComponent* oc = static_cast<OctreeComponent*>(entity->components[Component::Type::Octree].get());
    int size = sizeof(uint32_t) * oc->data.get()->size();
//    buffer->write(oc->data->data(), size, endOffset);

    octreeOffsets[entity->getId()] = endOffset;
    renderOffsets.push_back(endOffset);
    endOffset += PAGE_BYTES;
}

void GPUMemoryManager::updateEntityOctree(Entity* entity) {
    OctreeComponent* oc = static_cast<OctreeComponent*>(entity->components[Component::Type::Octree].get());
    int offset = octreeOffsets[entity->getId()];
    int size = sizeof(uint32_t) * oc->data.get()->size();
//    GLvoid* data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset, size, GL_MAP_WRITE_BIT);
//    memcpy(data, oc->data.get()->data(), size);
//    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void GPUMemoryManager::updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform, Vulkan::Buffer* buffer) {
    int size = sizeof(glm::vec4) * transform.size();
    int offset = octreeOffsets[entity->getId()] + PAGE_BYTES - size;
//    buffer->write(transform.data(), size, offset);
}

void GPUMemoryManager::removeEntity(const Entity* entity) {

}

void GPUMemoryManager::updateRenderList(Vulkan::Buffer* buffer) {
    uint32_t count = renderOffsets.size();
//    buffer->write(&count, sizeof(count));
//    buffer->write(renderOffsets.data(), sizeof(renderOffsets[0]) * renderOffsets.size(), sizeof(count));
}

} // Origin
