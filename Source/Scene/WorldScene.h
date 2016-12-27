#pragma once
#include "Scene3D.h"
#include "../ECS/Entity.h"
#include "../Graphics/Vulkan/Pipeline/GraphicsPipeline.h"
#include "../Graphics/Vulkan/Pipeline/PipelineLayout.h"
#include "../Graphics/Vulkan/DescriptorSetLayout.h"
#include "../Graphics/Vulkan/Collection/DescriptorSetCollection.h"
#include "../Graphics/Vulkan/Collection/CommandBufferCollection.h"
#include "../Graphics/Vulkan/MemoryBuffer.h"
#include "../Graphics/Vulkan/DescriptorPool.h"
#include "../Graphics/Vulkan/Uniform.h"
#include <SDL.h>
#include <glm/glm.hpp>

class WorldScene : public Scene3D {

    struct UBOfrag {
        int pageBytes = PAGE_BYTES;
        int blockInfoEnd = BLOCK_INFO_END;

        int frameWidth;
        int frameHeight;

        glm::vec3 backgroundColor;
        glm::vec3 lightColor;
        glm::vec3 lightPos;
        bool shadeless = true;

        float ambientStrength = 0.1;
        float lod;
        int transformCount;

        glm::vec2 pickPixel = glm::vec2(-1, -1);
    } uboFrag;

    struct OctreeFrag {
        int count;
        uint data[];
    } octreeFrag;

    struct RenderList {
        int count;
        uint offsets[];
    } renderList;


public:
    WorldScene();
    ~WorldScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
    EntityId getCharacterId() { return characterId; }
    uint64_t getSeed() { return seed; }

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    Vulkan::PipelineLayout* pipelineLayout = nullptr;
    Vulkan::DescriptorPool* descriptorPool = nullptr;
    Vulkan::DescriptorSetLayout* descriptorSetLayout = nullptr;
    Vulkan::DescriptorSetCollection* descriptorSetCollection = nullptr;
    Vulkan::GraphicsPipeline* graphicsPipeline = nullptr;
    Vulkan::MemoryBuffer* vertexMemoryBuffer = nullptr;
    Vulkan::MemoryBuffer* indexMemoryBuffer = nullptr;
    Vulkan::CommandBufferCollection* commandBufferCollection = nullptr;
    Vulkan::Uniform* uniformFrag = nullptr;
    Vulkan::Uniform* octreeBuffer = nullptr;
    Vulkan::Uniform* renderListBuffer = nullptr;
    EntityId characterId;
    uint64_t seed;
};
