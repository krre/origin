#pragma once
#include "../UI/Control.h"
#include "../UI/Layout.h"
#include <vector>

class Scene2D : public Control {

public:
    Scene2D();
    void draw(float dt) override;

    void addControl(std::shared_ptr<Control> control);
    void removeControl(std::shared_ptr<Control> control);
    void clearControls();

    void setLayout(std::shared_ptr<Layout> layout);

private:
    void onWindowResize(int width, int height);

    std::vector<std::shared_ptr<Control>> controls;
    std::shared_ptr<Layout> layout;
};
