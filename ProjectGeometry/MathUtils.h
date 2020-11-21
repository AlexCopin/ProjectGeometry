#pragma once
#include "SFML/Graphics.hpp"
#include <math.h>
extern const float IIM_PI;
float ConvertRadToDeg(float radian);
float ConvertDegToRad(float degree);
float GetMax(float a, float b);
float GetMin(float a, float b);
int GetMax(int a, int b);
int GetMin(int a, int b);
float Magnitude(sf::Vector2f vdirection, sf::Vector2f vdirection2);
sf::Vector2f VectorNewAngle(float angle, sf::Vector2f direction);
sf::Vector2f Normalized(sf::Vector2f vector);