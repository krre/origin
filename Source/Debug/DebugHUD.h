#pragma once
#include "UI/Control.h"

namespace Origin {

class Label;

class DebugHUD : public Control {

public:
    DebugHUD(Control* parent = nullptr);
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
