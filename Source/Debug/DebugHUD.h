#pragma once
#include "../Core/Singleton.h"
#include "../Graphics/Scene2D.h"
#include "../UI/Text.h"
#include "../UI/LinearLayout.h"

class DebugHUD : public Singleton<DebugHUD>, public Scene2D {

public:
    DebugHUD();
    void draw(float dt) override;
    void trigger();

private:
    Text fps;
    Text version;
    float accumTime = 0.5;
    int counter = 30;
    std::shared_ptr<LinearLayout> statisticsLayout = std::make_shared<LinearLayout>(LinearLayout::VERICAL);
};
