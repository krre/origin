#pragma once
#include "../Core/Singleton.h"
#include "../Graphics/Drawable.h"
#include "../UI/Text.h"

class DebugHUD : public Singleton<DebugHUD>, public Drawable {

public:
    DebugHUD();
    void draw(float dt) override;
    void trigger();

private:
    Text fpsText;
};
