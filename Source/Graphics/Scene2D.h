#pragma once
#include "Drawable.h"
#include "../UI/Control.h"
#include <vector>

class Scene2D : public Drawable {

public:
    Scene2D();
    void draw(float dt) override;
    void addControl(std::shared_ptr<Control> control);
    void removeControl(std::shared_ptr<Control> control);
    void clearControls();

private:
    void onWindowResize(int width, int height);

    std::vector<std::shared_ptr<Control>> controls;
};
