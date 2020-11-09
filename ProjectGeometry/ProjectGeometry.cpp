#include "ProjectGeometry.h"
// Julien: LOG MACRO
#define LOG(X) std::cout << X << std::endl;
//
std::string getAppPath()
{
    char cAppPath[MAX_PATH];
    GetModuleFileNameA(0, cAppPath, MAX_PATH);
    std::string sAppPath = cAppPath;
    char appNamePos = sAppPath.find_last_of("\\");
    return sAppPath.substr(0, appNamePos + 1);
}
std::string getAssetsPath()
{
    return getAppPath() + "\\Assets\\";
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "ProjectGeometry");
    sf::Clock(clock);
    // Start Function
    sf::Font(font);
    font.loadFromFile(getAssetsPath() + "arial.ttf");
    sf::Text(text);
    text.setFont(font);
    text.setString("GG ALEX");
    sf::Texture(texture);
    texture.loadFromFile(getAssetsPath() + "brain.jpg");
    sf::Sprite(sprite);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    //
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        window.clear();
        // Update Function
        window.draw(text);
        window.draw(sprite);
        //
        window.display();
    }
}