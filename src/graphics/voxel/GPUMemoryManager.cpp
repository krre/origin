#include "GPUMemoryManager.h"
#include "ecs/components/Components.h"
#include "ecs/Entity.h"
#include "vulkan/api/buffer/Buffer.h"

GPUMemoryManager::GPUMemoryManager() {
}

void GPUMemoryManager::addEntity(Entity* entity, Vulkan::Buffer* buffer) {
    OctreeComponent* oc = entity->octree();
//    int size = sizeof(uint32_t) * oc->data.get()->size();
//    buffer->write(oc->data->data(), size, endOffset);

    m_octreeOffsets[entity->id()] = endOffset;
    renderOffsets.push_back(endOffset);
    endOffset += Core::PAGE_BYTES;
}

void GPUMemoryManager::updateEntityOctree(Entity* entity) {
    OctreeComponent* oc = entity->octree();
    int offset = m_octreeOffsets[entity->id()];
//    int size = sizeof(uint32_t) * oc->data.get()->size();
//    GLvoid* data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset, size, GL_MAP_WRITE_BIT);
//    memcpy(data, oc->data.get()->data(), size);
//    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void GPUMemoryManager::updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform, Vulkan::Buffer* buffer) {
    int size = sizeof(glm::vec4) * transform.size();
    int offset = m_octreeOffsets[entity->id()] + Core::PAGE_BYTES - size;
//    buffer->write(transform.data(), size, offset);
}

void GPUMemoryManager::removeEntity(const Entity* entity) {

}

void GPUMemoryManager::updateRenderList(Vulkan::Buffer* buffer) {
    uint32_t count = renderOffsets.size();
//    buffer->write(&count, sizeof(count));
//    buffer->write(renderOffsets.data(), sizeof(renderOffsets[0]) * renderOffsets.size(), sizeof(count));
}
