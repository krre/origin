#pragma once
#include "../Core/Singleton.h"
#include "../Scene/Scene2D.h"
#include "../UI/Text.h"
#include "../UI/LinearLayout.h"
#include "../Event/Event.h"

class DebugHUD : public Singleton<DebugHUD>, public Scene2D {

public:
    DebugHUD();
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
    void trigger();

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    void onWindowResize(int width, int height) override;

    Text fps;
    Text version;
    Text openGL;
    Text vendor;
    Text cpuCount;
    Text systemRAM;
    Text posX;
    Text posY;
    Text posZ;
    float accumTime = 0.5;
    int counter = 30;
    std::shared_ptr<LinearLayout> statisticsLayout = std::make_shared<LinearLayout>(LinearLayout::VERICAL);
};
