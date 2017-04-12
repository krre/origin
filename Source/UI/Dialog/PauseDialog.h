#pragma once
#include "Dialog.h"

class PauseDialog : public Dialog {

public:
    PauseDialog();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;

private:
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
    void buildCommandBuffers() override;
};
