#pragma once
#include "Scene/Scene2D.h"

class SettingsScene : public Scene2D {

public:
    SettingsScene();
    ~SettingsScene();
    void init() override;
    void update(float dt) override;

private:
    void create();
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
};
