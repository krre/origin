#pragma once
#include "ui/Control.h"

class Label;

class DebugHUD : public Control {
public:
    DebugHUD(Control* parent = nullptr);

private:
    void updateImpl(float dt) override;

    float m_accumTime = 0.5;
    int m_counter = 30;
    int m_fps = 0;
    std::string m_vulkanApiVersion;
    Label* m_label = nullptr;
};
