#pragma once
#include "Main.h"
class Ship : Object
{
public:
	float posX;
	float posY;
	sf::CircleShape shipShape;
	std::size_t count = 3;

	Ship* CreateShip(float x, float y, std::string id);
	void Start(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float deltaTime);
	void RotateShip(sf::RenderWindow* window);
};