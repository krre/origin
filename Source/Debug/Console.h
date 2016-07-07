#pragma once
#include "../Core/Singleton.h"

class Console : public Singleton<Console> {

public:
    Console();
    void render(float dt);
    void setVisible(bool visible);
    bool getVisible() { return visible; }

private:
    bool visible = false;
};
