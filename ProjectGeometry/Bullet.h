#pragma once
#include "Main.h"
#include "Player.h"
class Bullet : Object
{
public:
	int damageB = 2;
	float speedB = 10.0f;
	float scaleB = 0.5f;
	float radiusB = 10.0f;
	sf::CircleShape shapeB;
	sf::Vector2f trajectoire;
	Bullet(int damage, sf::Vector2f direction, float speed);
	void Update(sf::RenderWindow* window, float deltaTime);
	void MoveBullet();
};