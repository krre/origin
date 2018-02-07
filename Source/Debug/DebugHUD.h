#pragma once
#include "Screen/Screen.h"
#include "VulkanRenderer/API/Pipeline/PipelineCache.h"
#include "VulkanRenderer/ShaderProgram.h"
#include "VulkanRenderer/API/Sampler.h"
#include "VulkanRenderer/API/RenderPass.h"
#include <glm/glm.hpp>

namespace Origin {

class Label;

class DebugHUD : public Screen {

public:
    DebugHUD();
    ~DebugHUD();
    void trigger();

private:
    void updateImpl(float dt) override;

    float accumTime = 0.5;
    int counter = 30;
    int fps = 0;
    std::string vulkanApiVersion;
    Label* displayLabel;
};

} // Origin
