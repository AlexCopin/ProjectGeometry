#pragma once
#include "Main.h"
#include "Player.h"
class Bullet : Object
{
public:
	int damageB = 0;
	float speedB = 0.0f;
	sf::CircleShape shapeB;
	sf::Vector2f originPos;
	sf::Vector2f targetPos;
	Bullet(int damage, sf::Vector2f mousePos);
	float timeInSeconds = 0.0f;
	void Update(sf::RenderWindow* window, float deltaTime);
};