#include "Layout.h"

Layout::Layout() {

}

void Layout::resize(int width, int height) {
    for (auto layout : layouts) {
        layout->resize(width, height);
    }
}

void Layout::addLayout(std::shared_ptr<Layout> layout) {
    layouts.push_back(layout);
}

void Layout::removeLayout(std::shared_ptr<Layout> layout) {
    layouts.erase(std::remove(layouts.begin(), layouts.end(), layout), layouts.end());
}

void Layout::clearLayouts() {
    layouts.clear();
}

void Layout::setSpacing(int spacing) {
    this->spacing = spacing;
}
