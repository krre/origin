#pragma once
#include "Control.h"

class Label;
class Timer;

class Toast : public Control {

public:
    Toast(Control* parent = nullptr);
    ~Toast();
    void show(const std::string& toastText);

private:
    void onTimeout();
    Label* text;
    Timer* timer;
};
