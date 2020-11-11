#pragma once
#include "Main.h"
class Ship : Object
{
public:
	float posX;
	float posY;
	sf::CircleShape shipShape;
	Ship *CreateShip(float x, float y, sf::CircleShape shape);
};