#pragma once
#include "Graphics/Render/RenderState.h"

namespace Origin {

class VulkanRenderState : public RenderState {

public:
    VulkanRenderState();
    ~VulkanRenderState();
    void create() override;

private:

};

} // Origin
