#include "GPUMemoryManager.h"

GPUMemoryManager::GPUMemoryManager() {

}

void GPUMemoryManager::addEntity(const Entity* entity) {

}

void GPUMemoryManager::updateEntityOctree(const Entity* entity) {

}

void GPUMemoryManager::updateEntityTransform(const Entity* entity) {

}

void GPUMemoryManager::removeEntity(const Entity* entity) {

}

void GPUMemoryManager::beginBatch() {
    batch = true;
}

void GPUMemoryManager::endBatch() {
    batch = false;
}
