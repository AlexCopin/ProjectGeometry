#pragma once
#include "Main.h"
class Bullet : Object
{
public:
	int damageB = 0;
	float speedB = 0.0f;
	sf::CircleShape shapeB;
	float originPosX = 0.0f;
	float originPosY = 0.0f;
	void Update(sf::RenderWindow* window, float deltaTime);
};