#include "GameScreen.h"
#include <iostream>
#include <SDL_opengl.h>

GameScreen::GameScreen() {

}

void GameScreen::update() {

}

void GameScreen::render() {
    glClearColor(0.25, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
//    std::cout << "GameScreen render" << std::endl;
}
