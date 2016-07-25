#pragma once
#include "Drawable.h"
#include "../UI/Control.h"
#include "../UI/Layout.h"
#include <vector>

class Scene2D : public Drawable {

public:
    Scene2D();
    void draw(float dt) override;

    void addControl(std::shared_ptr<Control> control);
    void removeControl(std::shared_ptr<Control> control);
    void clearControls();

    void addLayout(std::shared_ptr<Layout> layout);
    void removeLayout(std::shared_ptr<Layout> layout);
    void clearLayouts();

private:
    void onWindowResize(int width, int height);

    std::vector<std::shared_ptr<Control>> controls;
    std::vector<std::shared_ptr<Layout>> layouts;
};
