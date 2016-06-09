#include "View.h"
#include "../Event/Event.h"
#include <SDL_opengl.h>

extern Event* event;

View::View() {
    ::event->render.connectMember(&View::render, this);
    ::event->update.connectMember(&View::update, this, std::placeholders::_1);
}

void View::update(double dt) {
//    print("update: " << dt);
}

void View::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Node* rootNode = scene->getRoot();
    rootNode->draw();
}
