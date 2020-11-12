#pragma once
#include "Main.h"
#include "Player.h"
class Ship : Object
{
public:
	sf::Vector2f posShip;
	sf::CircleShape shipShape;
	bool isWithPlayer = false;


	
	Ship(sf::Vector2f position, std::string id);
	void Start();
	void Update(sf::RenderWindow* window, float deltaTime);
	void RotateShip(sf::RenderWindow* window);
	void GetPlayer();
	void GetDistanceWithPlayer();

};