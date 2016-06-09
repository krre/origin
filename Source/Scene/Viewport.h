#pragma once
#include "../Core/Object.h"
#include "../UI/View.h"

typedef list<shared_ptr<View>> ViewList;

class Viewport : public Object {

public:
    Viewport();
    void addView(shared_ptr<View> view);
    void removeView(shared_ptr<View> view);

private:
    ViewList views;
};
