#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "littleShip.h"

struct Ship;

struct Player
{
	int lifeP = 0;
	int speedP = 0;
	sf::CircleShape playerShape;
	Ship** playerShips;
};