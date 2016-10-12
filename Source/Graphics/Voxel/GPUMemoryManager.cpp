#include "GPUMemoryManager.h"
#include "../../Resource/ResourceManager.h"

GPUMemoryManager::GPUMemoryManager() {
    voxelShaderGroup = ResourceManager::getInstance()->getShaderGroup("VoxelShaderGroup");
    program = voxelShaderGroup->getProgram();
    voxelShaderGroup->bind();
    glUniform1i(glGetUniformLocation(program, "octrees"), 0);

    glGenBuffers(1, &octreesTbo);
    glBindBuffer(GL_TEXTURE_BUFFER, octreesTbo);
    glBufferData(GL_TEXTURE_BUFFER, MEMORY_SIZE, NULL, GL_DYNAMIC_DRAW);

    glGenTextures(1, &octreesTexture);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32UI, octreesTbo);
}

void GPUMemoryManager::addEntity(const Entity* entity) {
    if (!batch) {
        bind();
    }
}

void GPUMemoryManager::updateEntityOctree(const Entity* entity) {
    if (!batch) {
        bind();
    }
}

void GPUMemoryManager::updateEntityTransform(const Entity* entity) {
    if (!batch) {
        bind();
    }
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
}

void GPUMemoryManager::release() {
    glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

void GPUMemoryManager::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, octreesTexture);
}
