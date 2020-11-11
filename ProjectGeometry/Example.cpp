#include "Main.h"
class Example : Object
{
    std::string id = "example";
    sf::Font(font);
    sf::Text(text);
    sf::Texture(texture);
    sf::Sprite(sprite);
    void Start(sf::RenderWindow *window)
    {
        font.loadFromFile(getAssetsPath() + "arial.ttf");
        text.setFont(font);
        text.setString("GG ALEX");
        texture.loadFromFile(getAssetsPath() + "brain.jpg");
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);
    }
    void Update(sf::RenderWindow *window)
    {
        window->draw(text);
        window->draw(sprite);
    }
};
Example *example = new Example;