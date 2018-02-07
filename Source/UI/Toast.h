#pragma once
#include "Control.h"

namespace Origin {

class Label;
class Timer;

class Toast : public Control {

public:
    Toast();
    void showToast(const std::string& toastText);

private:
    void drawImpl() override;
    void updateImpl(float dt) override;
    void onTimeout();
    Label* text;
    std::unique_ptr<Timer> timer;
};

} // Origin
