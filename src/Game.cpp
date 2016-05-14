#include "Game.h"

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 480;

Game::Game() : window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Gagarin") {

}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void Game::update() {
}

void Game::render() {
    window.clear(sf::Color(40, 40, 40));
    window.display();
}
