#pragma once
#include "../../Core/Common.h"
#include "../../Graphics/OpenGL/ShaderGroup.h"
#include "../../ECS/Entity.h"
#include <GL/glew.h>
#include <map>

constexpr int MEMORY_SIZE = (1 << 20) * 100; // 100 MB

class GPUMemoryManager {

public:
    GPUMemoryManager();
    void addEntity(Entity* entity);
    void updateEntityOctree(Entity* entity);
    void updateEntityTransform(const Entity* entity);
    void removeEntity(const Entity* entity);

    void beginBatch();
    void endBatch();

    void bind();
    void release();
    void use();

private:
    ShaderGroup* voxelShaderGroup;
    GLuint program;
    bool batch = false;
    GLuint octreesTbo;
    GLuint octreesTexture;
    int endOffset = 0;
    std::map<EntityId, int> octreeOffsets;
};
