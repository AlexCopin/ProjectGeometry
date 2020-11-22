#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <math.h>
#include "MathUtils.h"
#include "SFML/Audio.hpp"
// Julien: LOG MACRO
#define LOG(X) std::cout << X << std::endl;
// Julien: Utils
std::string getAppPath();
std::string getAssetsPath();
// Julien: API
class Map;
class Object
{
public:
    std::string id;
    bool isActive = 1;
    Object();
    ~Object();
    virtual void Start(sf::RenderWindow *window){};
    virtual void Update(sf::RenderWindow *window, float deltaTime){};
    virtual void OnEvent(sf::RenderWindow *window, sf::Event event, float deltaTime){};
};
class Object2
{
public:
    // std::string id;
    bool isActive = 1;
    Object2();
    virtual ~Object2();
    virtual void Start(sf::RenderWindow *window){};
    virtual void Update(sf::RenderWindow *window, float deltaTime){};
};
Object *FindObject(std::string id);
bool SetActive(void *object, bool isActive);
bool DestroyObject(void *object);
bool DestroyObject2(Object2 *object2);
bool MouseButtonDown(bool boule);
bool MouseButtonUp(bool boule);
void BeginGame(sf::RenderWindow &window, sf::Font police);
class Enemy;
std::vector<Enemy *> &getEnemies();
sf::Sound* getSoundPlayer();
sf::Sound* getSoundEnemy();
sf::Music* getMusic();