#pragma once
#include "../../Core/Common.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include "../../ECS/Entity.h"
#include <GL/glew.h>
#include <map>
#include <glm/glm.hpp>

constexpr int MEMORY_SIZE = (1 << 20) * 100; // 100 MB

class GPUMemoryManager {

public:
    GPUMemoryManager();
    void addEntity(Entity* entity);
    void updateEntityOctree(Entity* entity);
    void updateEntityTransform(Entity* entity, const std::vector<glm::vec4>& transform);
    void removeEntity(const Entity* entity);

    void beginBatch();
    void endBatch();

    void bind();
    void release();

    std::map<EntityId, int> getOctreeOffsets() const { return octreeOffsets; }

private:
    ShaderGroup* voxelShaderGroup;
    GLuint program;
    bool batch = false;
    GLuint octreesSsbo;
    int endOffset = 0;
    std::map<EntityId, int> octreeOffsets;
};
