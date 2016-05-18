#include "MainScreen.h"
#include <iostream>
#include <SDL_opengl.h>

MainScreen::MainScreen() {

}

void MainScreen::update() {

}

void MainScreen::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "MainScreen render" << std::endl;
}
