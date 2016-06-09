#include "Viewport.h"

Viewport::Viewport() {

}

void Viewport::addView(shared_ptr<View> view) {
    views.push_back(view);
}

void Viewport::removeView(shared_ptr<View> view) {
    views.remove(view);
}
