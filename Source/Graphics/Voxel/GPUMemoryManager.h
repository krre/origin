#pragma once
#include "../../Core/Common.h"
#include "../../ECS/Entity.h"
#include "../Vulkan/Descriptor/Descriptor.h"
#include <map>
#include <vector>
#include <glm/glm.hpp>

constexpr int MEMORY_SIZE = (1 << 20) * 100; // 100 MB
const int MAX_OCTREE_COUNT = 100;

class GPUMemoryManager {

public:
    GPUMemoryManager();
    void addEntity(Entity* entity, Vulkan::Descriptor* descriptor);
    void updateEntityOctree(Entity* entity);
    void updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform);
    void removeEntity(const Entity* entity);

    void updateRenderList();
    std::map<EntityId, int> getOctreeOffsets() const { return octreeOffsets; }

private:
//    ShaderGroup* voxelShaderGroup;
//    GLuint program;
    bool batch = false;
//    GLuint octreesSsbo;
//    GLuint renderListSsbo;
    int endOffset = 0;
    std::map<EntityId, int> octreeOffsets;
    std::vector<uint32_t> renderOffsets;
};
