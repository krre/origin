#include "View.h"
#include "../Core/App.h"
#include <SDL_opengl.h>

App* app;

View::View() {
    ::app->render.connectMember(&View::render, this);
    ::app->update.connectMember(&View::update, this, std::placeholders::_1);
}

void View::update(double dt) {
//    print("update: " << dt);
}

void View::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
