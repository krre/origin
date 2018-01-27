#pragma once
#include <vector>

namespace Origin {

class Control;
class Screen;

class Layout {

public:
    Layout();
    virtual ~Layout();

    void addControl(Control *control);
    void removeControl(Control* control);
    void clearControls();

    void addLayout(Layout* layout);
    void removeLayout(Layout* layout);
    void clearLayouts();

    int getSpacing() const { return spacing; }
    void setSpacing(int spacing);

    void update(float dt);
    void draw();

    void resize(int width, int height);

    void setScreen(Screen* screen);

protected:
    virtual void updateContentPostion() = 0;

    std::vector<Control*> controls;
    std::vector<Layout*> layouts;
    int spacing = 5;
    Control* parent = nullptr;
    Screen* screen = nullptr;
};

} // Origin
