#pragma once
#include "Rectangle.h"
#include <vector>

class Layout : public Rectangle {

public:
    Layout();
    virtual void resize(int width, int height);

    void addControl(std::shared_ptr<Control> control);
    void removeControl(std::shared_ptr<Control> control);
    void clearControls();

    void addLayout(std::shared_ptr<Layout> layout);
    void removeLayout(std::shared_ptr<Layout> layout);
    void clearLayouts();

    int getSpacing() const { return spacing; }
    void setSpacing(int spacing);

    void setParent(Control* parent);

private:
    std::vector<std::shared_ptr<Control>> controls;
    std::vector<std::shared_ptr<Layout>> layouts;
    int spacing = 10;
    Control* parent = nullptr;
};
