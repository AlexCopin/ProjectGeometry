#include "Main.h"
#include "Map.h";
#include "Background.h"
#include "Enemy.h"
const float ENTITY_SPAWN_PERIOD = 1.0f;
const int NUMBER_STARS = 500;
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
std::vector<Object2 *> Objects2;
Object2::Object2()
{
    Objects2.push_back(this);
}
Object2::~Object2()
{
    Objects2.erase(std::find(Objects2.begin(), Objects2.end(), this));
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
bool DestroyObject2(void *object2)
{
    if (object2)
    {
        ((Object2 *)object2)->~Object2();
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
    sf::RenderWindow window(sf::VideoMode(1600, 950), "ProjectGeometry", sf::Style::Default, settings);
    window.setMouseCursorVisible(false);
    sf::Clock(clock);
    auto map = new Map("map", &window);
    auto background = new Background("background", &window);
    //TEST ENTITIES
    float entitySpawnTimer = 0.0f;
    std::list<Entity *> entities;
    std::list<Entity *>::iterator entityIt = entities.begin();
    //STARS
    std::list<Star *> stars;
    std::list<Star *>::iterator starsIt = stars.begin();
    for (int i = 0; i < NUMBER_STARS; i++)
    {
        float randomX = rand() * window.getSize().x / (float)RAND_MAX;
        float randomY = rand() * window.getSize().y / (float)RAND_MAX;
        float colorAlpha = 1 + (rand() % 256);
        sf::Color color(255, 255, 255, colorAlpha);
        float sizeStar = 1 + (rand() % 3);
        Star *star = new Star(randomX, randomY, color, sizeStar);
        stars.push_back(star);
    }
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
        // HOW TO MANAGE LIFE OF GAME ENTITIES
        entitySpawnTimer += deltaTime;
        if (entitySpawnTimer > ENTITY_SPAWN_PERIOD)
        {
            entitySpawnTimer = 0.0f;
            float randomX = rand() * window.getSize().x / (float)RAND_MAX;
            float randomY = rand() * window.getSize().y / (float)RAND_MAX;
            float randomAngle = rand() * 360.0f / (float)RAND_MAX;
            Entity *pNewEntity = background->CreateEntity(randomX, randomY, randomAngle);
            entities.push_back(pNewEntity);
        }
        entityIt = entities.begin();
        while (entityIt != entities.end())
        {
            background->UpdateB(*entityIt, deltaTime);
            if (!background->IsAlive(*entityIt))
            {
                background->Destroy(*entityIt);
                entityIt = entities.erase(entityIt);
            }
            else
            {
                entityIt++;
            }
        }
        //STARS
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
        for (auto i : Objects2)
            if (i)
                if (i->isActive)
                    i->Update(&window, deltaTime);
        Player::player->ShootBullet(&window, deltaTime);
        Player::player->ShipShootBullet(&window, deltaTime);
        window.draw(aimShape);
        entityIt = entities.begin();
        while (entityIt != entities.end())
        {
            background->DrawEntity(*entityIt, window);
            entityIt++;
        }
        starsIt = stars.begin();
        while (starsIt != stars.end())
        {
            (*starsIt)->DrawStars(&window);
            starsIt++;
        }
        window.display();
    }
    entityIt = entities.begin();
    while (entityIt != entities.end())
    {
        background->Destroy(*entityIt);
        entityIt++;
    }
}