#pragma once
#include "Control.h"

class Label;
class Timer;

class Toast : public Control {
public:
    Toast(Control* parent = nullptr);

    void show(const std::string& toastText);

private:
    void onTimeout();
    Label* m_text = nullptr;
    Timer* m_timer = nullptr;
};
