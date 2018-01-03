#pragma once
#include "Scene/Scene2D.h"

namespace Origin {

class SettingsScene : public Scene2D {

public:
    SettingsScene();
    ~SettingsScene();
    void init() override;
    void update(float dt);

private:
    void create();
//    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
};

} // Origin
