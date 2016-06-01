#pragma once
#include "../UI/View.h"
#include "Object.h"
#include <list>

typedef list<shared_ptr<View>> ViewList;

class Game : public Object {

public:
    Game();
    void addView(shared_ptr<View> view);
    void removeView(shared_ptr<View> view);
    void update(double dt);
    void render();

private:
    ViewList views;
};
