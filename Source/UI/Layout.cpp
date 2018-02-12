#include "Layout.h"
#include "Control.h"
#include <algorithm>

namespace Origin {

Layout::Layout(Control* parent) : Control(parent) {

}

void Layout::notifyAddChild(Object* child) {
    updateContentPostion();
}

void Layout::notifyRemoveChild(Object* child) {
    updateContentPostion();
}

void Layout::setSpacing(int spacing) {
    this->spacing = spacing;
}

} // Origin
