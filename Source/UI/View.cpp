#include "View.h"
#include <SDL_opengl.h>

View::View() {

}

void View::update(double dt) {

}

void View::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
