#pragma once
#include "../Graphics/Drawable.h"
#include "Text.h"
#include "../Core/Timer.h"

class Toast : public Covenantland::Drawable {

public:
    Toast();
    void draw(float dt) override;
    void update(float dt) override;
    void showToast(const std::string& toastText);

private:
    void onTimeout();
    Text text;
    Timer timer;
};
