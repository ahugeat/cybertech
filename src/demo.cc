#include <iostream>

#include <SFML/Graphics.hpp>

int main(void) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "CyberTech - demo");

    while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // update

    // render


    window.display();
  }

    return EXIT_SUCCESS;
}
