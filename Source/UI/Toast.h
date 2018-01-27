#pragma once
#include "Graphics/Drawable.h"
#include "Label.h"
#include "Core/Timer.h"

namespace Origin {

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

} // Origin
