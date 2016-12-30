#pragma once
#include "Scene3D.h"
#include "../ECS/Entity.h"
#include "../UI/Viewport.h"
#include "../Graphics/Voxel/GPUMemoryManager.h"
#include "../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorSetLayout.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorSets.h"
#include "../Graphics/Vulkan/Command/CommandBuffers.h"
#include "../Graphics/Vulkan/Buffer.h"
#include "../Graphics/Vulkan/Descriptor/DescriptorPool.h"
#include "../Graphics/Vulkan/Descriptor/Descriptor.h"
#include <SDL.h>
#include <glm/glm.hpp>

const int LOD_PIXEL_LIMIT = 1;

class WorldScene : public Scene3D {

    struct UBO {
        int shadeless = 0;
        int pageBytes = PAGE_BYTES;
        int blockInfoEnd = BLOCK_INFO_END;
        int frameWidth;
        int frameHeight;
        int transformCount;

        float ambientStrength = 0.1;
        float lod;

        glm::vec4 backgroundColor = glm::vec4(0.77, 0.83, 0.83, 1.0);
        glm::vec4 lightColor;
        glm::vec4 lightPos;

        glm::vec4 pickPixel = glm::vec4(-1, -1, 0, 0);
    } ubo;

    struct PickResult {
        glm::vec3 pos;
        uint32_t parent;
        uint32_t scale;
        int childIdx;
    } pickResult;

    struct DebugOut {
        glm::vec4 debugVec;
        int debugInt;
        float debugFloat;
    } debugOut;

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

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    Vulkan::PipelineLayout* pipelineLayout = nullptr;
    Vulkan::DescriptorPool* descriptorPool = nullptr;
    Vulkan::DescriptorSetLayout* descriptorSetLayout = nullptr;
    Vulkan::DescriptorSets* descriptorSets = nullptr;
    Vulkan::GraphicsPipeline* graphicsPipeline = nullptr;
    Vulkan::Buffer* vertexBuffer = nullptr;
    Vulkan::Buffer* indexBuffer = nullptr;
    Vulkan::CommandBuffers* commandBuffers = nullptr;
    Vulkan::Descriptor* uniformFrag = nullptr;
    Vulkan::Descriptor* octreeBuffer = nullptr;
    Vulkan::Descriptor* renderListBuffer = nullptr;
    Vulkan::Descriptor* pickResultBuffer = nullptr;
    Vulkan::Descriptor* debugOutBuffer = nullptr;
    EntityId characterId;
    uint64_t seed;
    Viewport viewport;
};
