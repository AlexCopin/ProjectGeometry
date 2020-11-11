#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
// Julien: LOG MACRO
#define LOG(X) std::cout << X << std::endl;
// Julien: Utils
std::string getAppPath();
std::string getAssetsPath();
// Julien: API
struct Object
{
    std::string id;
    bool Active = 1;
    Object();
    ~Object();
    virtual void Start(sf::RenderWindow *window){};
    virtual void Update(sf::RenderWindow *window){};
};
Object *FindObject(std::string id);