#pragma once
#include "ui/Control.h"

class Screen;

class Layout : public Control {
public:
    Layout(Control* parent = nullptr);

    int spacing() const { return m_spacing; }
    void setSpacing(int spacing);

protected:
    virtual void updateContentPostion() = 0;

private:
    void notifyAddChild(Object* child) override;
    void notifyRemoveChild(Object* child) override;

    int m_spacing = 5;
};
