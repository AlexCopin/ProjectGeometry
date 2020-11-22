#pragma once
#include "Main.h"
class Player;
class Bullet :public Object2
{
public:
	long playerShips;
	float shieldFactor;
	enum class Type
	{
		Player,
		Enemy
	} type;
	float damageB;
	float scaleB = 0.6f;
	float radiusB = 10.0f;
	float speedB = 1000;
	sf::CircleShape shapeB;
	short count = 3;
	sf::Vector2f trajectoire;
	Bullet(float damage, sf::Vector2f direction, Type type);
	~Bullet();
	void Update(sf::RenderWindow *window, float deltaTime);
	void MoveBullet(float speed);
};