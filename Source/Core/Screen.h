#pragma once
#include "Common.h"
#include <vector>

class View;

class Screen {

public:
    Screen();
    virtual void hide();
    virtual void pause();
    virtual void resume();
    virtual void show();

    void update(float dt);
    void render();
    void resize(uint32_t width, uint32_t height);

    void pushView(const std::shared_ptr<View>& view);
    void popView();
    View* getCurrentView() const { return currentView; }

private:
    std::vector<std::shared_ptr<View>> views;
    View* currentView = nullptr;
    bool isPaused = true;
};
