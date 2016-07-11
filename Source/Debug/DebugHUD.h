#pragma once
#include "../Core/Singleton.h"
#include "../UI/Text.h"

class DebugHUD : public Singleton<DebugHUD> {

public:
    DebugHUD();
    void render(float dt);

    void trigger();

    void setVisible(bool visible);
    bool getVisible() const { return visible; }

private:
    bool visible = false;
    Text fpsText;
};
