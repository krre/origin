#pragma once
#include "../Core/Singleton.h"

class DebugHUD : public Singleton<DebugHUD> {

public:
    DebugHUD();

    void setVisible(bool visible);
    bool getVisible() const { return visible; }

private:
    bool visible = false;
};
