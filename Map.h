#pragma once
#include "Main.h"
#include "Player.h"
class Map :public Object
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
	float spawnEnemy01Value = 5.0f;
	float spawnEnemy02Value = 7.5f;
	float spawnEnemy03Value = 7.0f;
	float countdown = 15.0f;
	float countdownV = 10.0f;
	float difficulty = 0.9f;
	float compteurEnemy = 8.0f;
	float compteurEnemyValue = 8.0f;
	static Map *mape;
	Map(std::string id, sf::RenderWindow *window);
	void Update(sf::RenderWindow *window, float deltaTime);
	void CollisionPlayer(float deltaTime);
	void SpawnEnemies(sf::RenderWindow *window, float deltaTime);
};