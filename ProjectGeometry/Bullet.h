#pragma once
#include "Main.h"
#include "Player.h"
class Bullet : Object2
{
public:
	enum TypeBullet
	{
	};
	int damageB = 2;
	float scaleB = 0.6f;
	float radiusB = 10.0f;
	float speedB = 1000;
	sf::CircleShape shapeB;
	sf::Vector2f trajectoire;
	Bullet(int damage, sf::Vector2f direction);
	void Update(sf::RenderWindow *window, float deltaTime);
	void MoveBullet(float speed);
};