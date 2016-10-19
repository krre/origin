#include "GPUMemoryManager.h"
#include "../../Resource/ResourceManager.h"
#include "../../ECS/Components/Components.h"

GPUMemoryManager::GPUMemoryManager() {
    voxelShaderGroup = ResourceManager::getInstance()->getShaderGroup("VoxelShaderGroup");
    program = voxelShaderGroup->getProgram();
    voxelShaderGroup->bind();

    glGenBuffers(1, &octreesSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, octreesSsbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, MEMORY_SIZE, NULL, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, octreesSsbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glUniform1i(glGetUniformLocation(program, "octrees"), 0);

    glGenBuffers(1, &octreesTbo);
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBufferData(GL_TEXTURE_BUFFER, MEMORY_SIZE, NULL, GL_DYNAMIC_DRAW);

    glGenTextures(1, &octreesTexture);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, octreesTbo);
}

void GPUMemoryManager::addEntity(Entity* entity) {
    if (!batch) {
        bind();
    }

    OctreeComponent* oc = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
    glBufferSubData(GL_TEXTURE_BUFFER, endOffset, sizeof(uint32_t) * oc->data.get()->size(), oc->data.get()->data());
    octreeOffsets[entity->getId()] = endOffset;
    endOffset += pageBytes;
}

void GPUMemoryManager::updateEntityOctree(Entity* entity) {
    if (!batch) {
        bind();
    }

    int offset = octreeOffsets[entity->getId()];
    OctreeComponent* oc = static_cast<OctreeComponent*>(entity->components[ComponentType::Octree].get());
    glBufferSubData(GL_TEXTURE_BUFFER, offset, sizeof(uint32_t) * oc->data.get()->size(), oc->data.get()->data());
}

void GPUMemoryManager::updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform) {
    if (!batch) {
        bind();
    }

    int size = sizeof(glm::vec4) * transform.size();
    int offset = octreeOffsets[entity->getId()] + pageBytes - size;
    glBufferSubData(GL_TEXTURE_BUFFER, offset, size, transform.data());

    GLvoid* data = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset, size, GL_MAP_WRITE_BIT);
//    print(data);
    memcpy(data, transform.data(), size);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

}

void GPUMemoryManager::removeEntity(const Entity* entity) {
    if (!batch) {
        bind();
    }
}

void GPUMemoryManager::beginBatch() {
    bind();
    batch = true;
}

void GPUMemoryManager::endBatch() {
    release();
    batch = false;
}

void GPUMemoryManager::bind() {
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, octreesSsbo);
}

void GPUMemoryManager::release() {
    glBindBuffer(GL_TEXTURE_BUFFER, 0);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void GPUMemoryManager::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);
}
