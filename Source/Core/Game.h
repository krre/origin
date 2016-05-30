#pragma once
#include "../UI/View.h"
#include <memory>
#include <list>

typedef std::list<std::shared_ptr<View>> ViewList;

class Game {

public:
    Game();
    void addView(std::shared_ptr<View> view);
    void removeView(std::shared_ptr<View> view);
    void update(double dt);

private:
    ViewList views;
};
