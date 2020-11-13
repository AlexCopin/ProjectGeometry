#include "Main.h"
//#include "Player.h"
// Julien: Utils
#include "Map.h";

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
// Julien: API
std::vector<Object *> Objects;
Object::Object()
{
    Objects.push_back(this);
}
Object::~Object()
{
    Objects.erase(std::find(Objects.begin(), Objects.end(), this));
}
Object *FindObject(std::string id)
{
    for (auto i : Objects)
        if (i->id == id)
            return i;
    return 0;
}
bool SetActive(void *object, bool isActive)
{
    if (object)
    {
        ((Object *)object)->isActive = isActive;
        return 1;
    }
    else
        return 0;
}
bool DestroyObject(void *object)
{
    if (object)
    {
        ((Object *)object)->~Object();
        return 1;
    }
    else
        return 0;
}
bool MouseButtonDown(bool boule)
{
    return boule;
}
bool MouseButtonUp(bool boule)
{
    return boule;
}
int main()
{
    // MouseCursor

    sf::CircleShape aimShape;
    float aimRadius = 10.0f;
    aimShape.setRadius(aimRadius);
    aimShape.setOrigin(aimRadius, aimRadius);
    aimShape.setFillColor(sf::Color::Transparent);
    aimShape.setOutlineColor(sf::Color::Red);
    aimShape.setOutlineThickness(2.0f);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1000, 600), "ProjectGeometry", sf::Style::Default, settings);
    window.setMouseCursorVisible(false);
    sf::Clock(clock);

    auto map = new Map("map", &window);

    while (window.isOpen())
    {
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            for (auto i : Objects)
                if (i)
                    if (i->isActive)
                        i->OnEvent(&window, event, deltaTime);

        }
        window.clear();
        //MouseCursor
        sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition(mousePositionInt);
        aimShape.setPosition(mousePosition);
        // Julien: Update Function
        for (auto i : Objects)
            if (i)
                if (i->isActive)
                    i->Update(&window, deltaTime);

        window.draw(aimShape);
        window.display();
    }
}