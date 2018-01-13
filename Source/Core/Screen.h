#pragma once
#include "Common.h"
#include <vector>

namespace Origin {

class Control;
class RenderWindow;
class View;
class View2D;
class View3D;
class Batch2D;

class Screen {

public:

    enum class Name {
        Menu,
        Settings,
        Game
    };

    Screen();
    ~Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void setRootControl(Control* control);
    Control* getRootControl() const { return rootControl; }

    void update(float dt);
    void resize(uint32_t width, uint32_t height);

private:
    void getBatches(Control* control, std::vector<Batch2D>& batches, std::vector<float>& vertices);
    void addView(View* view);

    Control* rootControl = nullptr;
    bool isPaused = true;
    std::vector<Batch2D> batches;
    std::vector<float> vertices;
    std::vector<View3D*> renderViews;
};

} // Origin
