#pragma once
#include "Graphics/Drawable.h"
#include "Text/Label.h"
#include "Core/Timer.h"

class Toast : public Drawable {

public:
    Toast();
    void draw(float dt) override;
    void update(float dt) override;
    void showToast(const std::string& toastText);

private:
    void onTimeout();
    Label text;
    Timer timer;
};
