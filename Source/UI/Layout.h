#pragma once
#include "UI/Control.h"
#include <vector>

namespace Origin {

class Screen;

class Layout : public Control {

public:
    Layout(Control* parent = nullptr);
    virtual ~Layout();

    void addLayout(Layout* layout);
    void removeLayout(Layout* layout);
    void clearLayouts();

    int getSpacing() const { return spacing; }
    void setSpacing(int spacing);

    void resize(int width, int height);

protected:
    virtual void updateContentPostion() = 0;

private:
    void notifyAddChild(Object* child) override;
    void notifyRemoveChild(Object* child) override;

    std::vector<Layout*> layouts;
    int spacing = 5;
};

} // Origin
