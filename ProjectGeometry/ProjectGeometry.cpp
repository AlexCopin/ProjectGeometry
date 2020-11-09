
#include <iostream>
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ChronoSpacer"); //, sf::Style::Fullscreen
    // Initialise everything below
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Process any input event here
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        window.clear();
        // Whatever I want to draw goes here
        window.display();
    }
}