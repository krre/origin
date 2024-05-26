#pragma once
#include "Core/Common.h"
#include <map>
#include <vector>
#include <glm/glm.hpp>

namespace Origin {

constexpr int MEMORY_SIZE = (1 << 20) * 100; // 100 MB
const int MAX_OCTREE_COUNT = 100;

namespace Vulkan {
    class Buffer;
}

class Entity;

class GPUMemoryManager {

public:
    GPUMemoryManager();
    void addEntity(Entity* entity, Vulkan::Buffer* buffer);
    void updateEntityOctree(Entity* entity);
    void updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform, Vulkan::Buffer* buffer);
    void removeEntity(const Entity* entity);

    void updateRenderList(Vulkan::Buffer* buffer);
    std::map<Core::EntityId, int> getOctreeOffsets() const { return octreeOffsets; }

private:
    int endOffset = 0;
    std::map<Core::EntityId, int> octreeOffsets;
    std::vector<uint32_t> renderOffsets;
};

} // Origin
