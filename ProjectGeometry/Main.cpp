#include "Main.h"
// Julien: Utils
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
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "ProjectGeometry");
    sf::Clock(clock);
    // Julien: Start Function
    for (auto i : Objects)
        if (i->isActive)
            i->Start(&window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        float deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        window.clear();
        // Julien: Update Function
        for (auto i : Objects)
            if (i->isActive)
                i->Update(&window, deltaTime);
        window.display();
    }
}