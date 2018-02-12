#pragma once
#include "UI/Control.h"
#include <vector>

namespace Origin {

class Screen;

class Layout : public Control {

public:
    Layout(Control* parent = nullptr);

    int getSpacing() const { return spacing; }
    void setSpacing(int spacing);

protected:
    virtual void updateContentPostion() = 0;

private:
    void notifyAddChild(Object* child) override;
    void notifyRemoveChild(Object* child) override;

    int spacing = 5;
};

} // Origin
