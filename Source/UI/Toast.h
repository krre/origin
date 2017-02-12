#pragma once
#include "../Graphics/Drawable.h"
#include "Text/Text.h"
#include "../Core/Timer.h"

class Toast : public Origin::Drawable {

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
