#pragma once
#include "ui/Control.h"

class Label;

class DebugHUD : public Control {

public:
    DebugHUD(Control* parent = nullptr);
    ~DebugHUD();

private:
    void updateImpl(float dt) override;

    float accumTime = 0.5;
    int counter = 30;
    int fps = 0;
    std::string vulkanApiVersion;
    Label* label;
};
