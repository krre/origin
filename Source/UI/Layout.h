#pragma once
#include "UI/Control.h"
#include <vector>

namespace Origin {

class Screen;

class Layout : public Control {

public:
    Layout(Control* parent = nullptr);
    virtual ~Layout();

    void addControl(Control *control);
    void removeControl(Control* control);
    void removeControl(int index);
    void clearControls();

    void addLayout(Layout* layout);
    void removeLayout(Layout* layout);
    void clearLayouts();

    int getSpacing() const { return spacing; }
    void setSpacing(int spacing);

    void resize(int width, int height);

protected:
    virtual void updateContentPostion() = 0;

    std::vector<Layout*> layouts;
    int spacing = 5;
    Control* parent = nullptr;
};

} // Origin
