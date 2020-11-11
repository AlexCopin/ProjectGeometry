#include "Example1.h"
void Example1::Start(sf::RenderWindow *window)
{
    this->id = "example1";
    font.loadFromFile(getAssetsPath() + "arial.ttf");
    text.setFont(font);
    text.setString("GG ALEX");
    texture.loadFromFile(getAssetsPath() + "brain.jpg");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);
}
void Example1::Update(sf::RenderWindow *window, float deltaTime)
{
    window->draw(text);
    window->draw(sprite);
}
auto Example1InstantiateAtStart = new Example1;