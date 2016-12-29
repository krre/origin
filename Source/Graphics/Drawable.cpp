#include "Drawable.h"

using namespace Covenantland;

Drawable::Drawable() {

}

void Drawable::setVisible(bool visible) {
    this->visible = visible;
}

void Drawable::setOpacity(float opacity) {
    this->opacity = opacity;
}
