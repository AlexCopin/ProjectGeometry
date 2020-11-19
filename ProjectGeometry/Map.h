#pragma once
#include "Main.h"
#include "Player.h"
class Map : Object
{
public:
	std::string id;
	sf::RectangleShape limitUP;
	sf::RectangleShape limitRIGHT;
	sf::RectangleShape limitDOWN;
	sf::RectangleShape limitLEFT;
	Player *player;

	float spawnEnemy01 = 2.0f;
	float spawnEnemy02 = 3.0f;
	float spawnEnemy03 = 3.0f;
	float spawnEnemy04 = 15.0f;
	float spawnEnemy01Value = 2.0f;
	float spawnEnemy02Value = 3.0f;
	float spawnEnemy03Value = 3.0f;
	float spawnEnemy04Value = 15.0f;

	int compteurEnemy = 5;
	int compteurEnemyValue = 5;

	static Map* mape;
	Map(std::string id, sf::RenderWindow *window);
	void Update(sf::RenderWindow *window, float deltaTime);
	void CollisionPlayer(float deltaTime);
	void SpawnEnemies(sf::RenderWindow* window, float deltaTime);
};