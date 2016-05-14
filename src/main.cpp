#include <stdlib.h>
#include <SFML/Window.hpp>

int main(int argc, char* argv[]) {
    sf::Window App(sf::VideoMode(800, 600), "Gagarin");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                App.close();
            }
        }
        App.display();
    }

    return EXIT_SUCCESS;
}
