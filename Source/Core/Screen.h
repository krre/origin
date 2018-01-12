#pragma once
#include "Common.h"
#include <vector>

namespace Origin {

class Control;
class View;
class RenderWindow;

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

    void pushView(const std::shared_ptr<View>& view);
    void popView();
    View* getCurrentView() const { return currentView; }

private:
    Control* rootControl = nullptr;
    std::vector<std::shared_ptr<View>> views;
    std::vector<View*> renderViews;
    View* currentView = nullptr;
    bool isPaused = true;
    RenderWindow* window = nullptr;
};

} // Origin
