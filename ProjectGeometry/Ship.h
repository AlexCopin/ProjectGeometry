#pragma once
#include "Main.h"
class Player;
class Ship : Object
{
public:
	sf::Vector2f posShip;
	sf::CircleShape shipShape;
	bool isWithPlayer = false;


	Player* player = nullptr;
	Ship(sf::Vector2f position, std::string id);
	void Start(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float deltaTime);
	void RotateShip(sf::RenderWindow* window);
	void GetPlayer();
	void GetDistanceWithPlayer();

};