#pragma once
#include "Main.h"
#include "Player.h"
//#include "Player.h"
//#include "Enemy.h"

class Map : Object
{
public:
	std::string id;
	sf::RectangleShape limitUP;
	sf::RectangleShape limitRIGHT;
	sf::RectangleShape limitDOWN;
	sf::RectangleShape limitLEFT;

	Player *player;

	Map(std::string id, sf::RenderWindow *window);
	void Update(sf::RenderWindow *window, float deltaTime);
	void GetPlayerM();
	void CollisionPlayer();
};