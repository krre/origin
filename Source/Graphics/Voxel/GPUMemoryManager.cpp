#include "GPUMemoryManager.h"
#include "../../Resource/ResourceManager.h"
#include "../../ECS/Components/Components.h"

GPUMemoryManager::GPUMemoryManager() {
}

void GPUMemoryManager::addEntity(Entity* entity, Vulkan::Descriptor* descriptor) {
    OctreeComponent* oc = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
    int size = sizeof(uint32_t) * oc->data.get()->size();
    descriptor->update(endOffset, size, oc->data->data());

    octreeOffsets[entity->getId()] = endOffset;
    renderOffsets.push_back(endOffset);
    endOffset += PAGE_BYTES;
}

void GPUMemoryManager::updateEntityOctree(Entity* entity) {
    OctreeComponent* oc = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
    int offset = octreeOffsets[entity->getId()];
    int size = sizeof(uint32_t) * oc->data.get()->size();
//    GLvoid* data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset, size, GL_MAP_WRITE_BIT);
//    memcpy(data, oc->data.get()->data(), size);
//    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void GPUMemoryManager::updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform, Vulkan::Descriptor* descriptor) {
    int size = sizeof(glm::vec4) * transform.size();
    int offset = octreeOffsets[entity->getId()] + PAGE_BYTES - size;
    descriptor->update(offset, size, transform.data());
}

void GPUMemoryManager::removeEntity(const Entity* entity) {

}

void GPUMemoryManager::updateRenderList(Vulkan::Descriptor* descriptor) {
    uint32_t count = renderOffsets.size();
    descriptor->update(0, sizeof(count), &count);
    descriptor->update(sizeof(count), sizeof(renderOffsets[0]) * renderOffsets.size(), renderOffsets.data());
}
