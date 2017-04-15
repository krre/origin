#pragma once
#include "../Scene2D.h"
#include "../../UI/Button.h"
#include "../../UI/LinearLayout.h"

class SettingsScene : public Scene2D {

public:
    SettingsScene();
    ~SettingsScene();
    void init() override;
    void update(float dt) override;

private:
    void create();
    void writeCommands(Vulkan::CommandBuffer* commandBuffer) override;
};
