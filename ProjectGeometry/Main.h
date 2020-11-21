#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <math.h>
#include "MathUtils.h"
// Julien: LOG MACRO
#define LOG(X) std::cout << X << std::endl;
// Julien: Utils
std::string getAppPath();
std::string getAssetsPath();
// Julien: API
class Map;
struct Object
{
    std::string id;
    bool isActive = 1;
    Object();
    ~Object();
    virtual void Start(sf::RenderWindow *window){};
    virtual void Update(sf::RenderWindow *window, float deltaTime){};
    virtual void OnEvent(sf::RenderWindow *window, sf::Event event, float deltaTime){};
};
struct Object2
{
    // std::string id;
    bool isActive = 1;
    Object2();
    ~Object2();
    virtual void Start(sf::RenderWindow *window){};
    virtual void Update(sf::RenderWindow *window, float deltaTime){};
    virtual void OnEvent(sf::RenderWindow *window, sf::Event event, float deltaTime){};
};
Object *FindObject(std::string id);
bool SetActive(void *object, bool isActive);
bool DestroyObject(void *object);
bool DestroyObject2(void *object2);
bool MouseButtonDown(bool boule);
bool MouseButtonUp(bool boule);
void BeginGame(sf::RenderWindow &window, sf::Font police);
class Enemy;
std::vector<Enemy *> &getEnemies();