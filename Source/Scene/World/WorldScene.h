#pragma once
#include "../Scene3D.h"
#include "../../Graphics/ShaderProgram/VoxelShaderProgram.h"
#include "../../ECS/Entity.h"
#include "../../UI/Viewport.h"
#include "../../Graphics/Voxel/GPUMemoryManager.h"
#include "../../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../../Graphics/Vulkan/Buffer.h"
#include "../../Graphics/Plane.h"
#include <SDL.h>
#include <glm/glm.hpp>

const int LOD_PIXEL_LIMIT = 1;

class WorldScene : public Scene3D {

public:
    WorldScene();
    ~WorldScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
    void pause() override;
    void resume() override;
    EntityId getCharacterId() { return characterId; }
    uint64_t getSeed() { return seed; }
    void setSeed(uint64_t seed);

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void buildCommandBuffers() override;

    Vulkan::PipelineLayout pipelineLayout;
    Vulkan::GraphicsPipeline graphicsPipeline;
    Vulkan::Buffer* vertexBuffer = nullptr;
    Vulkan::Buffer* indexBuffer = nullptr;
    EntityId characterId;
    uint64_t seed;
    Viewport viewport;
    Plane plane;
    VoxelShaderProgram wsp;
};
