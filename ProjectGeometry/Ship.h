#pragma once
#include "Main.h"
class Ship : Object
{
public:
	sf::Vector2f posShip;
	sf::CircleShape shipShape;
	
	Ship(sf::Vector2f position, std::string id);
	void Update(sf::RenderWindow* window, float deltaTime);
	void RotateShip(sf::RenderWindow* window);

};