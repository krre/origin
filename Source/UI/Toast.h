#pragma once
#include "Control.h"

namespace Origin {

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
    std::unique_ptr<Timer> timer;
};

} // Origin
