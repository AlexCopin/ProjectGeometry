#include "Map.h"
#include "Enemy.h"
#include "Ship.h"
Map *Map::mape = nullptr;
Map::Map(std::string id, sf::RenderWindow *window)
{
	this->id = "Map";
	limitUP.setFillColor(sf::Color::Black);
	limitUP.setSize(sf::Vector2f(window->getSize().x, 100));
	limitUP.setPosition(sf::Vector2f(0, -90));
	limitDOWN.setFillColor(sf::Color::Black);
	limitDOWN.setSize(sf::Vector2f(window->getSize().x, 100));
	limitDOWN.setPosition(sf::Vector2f(0, window->getSize().y - 10));
	limitRIGHT.setFillColor(sf::Color::Black);
	limitRIGHT.setSize(sf::Vector2f(100, window->getSize().y));
	limitRIGHT.setPosition(sf::Vector2f(-90, 0));
	limitLEFT.setFillColor(sf::Color::Black);
	limitLEFT.setSize(sf::Vector2f(100, window->getSize().y));
	limitLEFT.setPosition(sf::Vector2f(window->getSize().x - 10, 0));
	player = new Player("Player", 1000, 50, 50);
	// Julien: testEnemy
	auto testEnemy0 = new Enemy("testEnemy0", sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2), Enemy::Type::Triangle);
	auto testEnemy1 = new Enemy("testEnemy1", sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2), Enemy::Type::Square);
	auto testEnemy2 = new Enemy("testEnemy2", sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2), Enemy::Type::Circle);
	mape = this;
}
void Map::Update(sf::RenderWindow *window, float deltaTime)
{
	CollisionPlayer(deltaTime);
	if (countdown <= 0)
	{
		if (spawnEnemy01Value >= 2.0f)
			spawnEnemy01Value *= difficulty;
		if (spawnEnemy02Value >= 3.0f)
			spawnEnemy02Value *= difficulty;
		if (spawnEnemy03Value >= 3.0f)
			spawnEnemy03Value *= difficulty;
		if (compteurEnemyValue >= 4.0f)
			compteurEnemyValue *= difficulty;
		countdown = countdownV;
	}
	if (countdown > 0)
	{
		countdown -= deltaTime;
	}
	window->draw(limitUP);
	window->draw(limitDOWN);
	window->draw(limitRIGHT);
	window->draw(limitLEFT);
}
void Map::CollisionPlayer(float deltaTime)
{
	if (limitUP.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(0, -1000 * deltaTime));
	}
	else if (limitDOWN.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(0, 1000 * deltaTime));
	}
	if (limitRIGHT.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(-1000 * deltaTime, 0));
	}
	else if (limitLEFT.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(1000 * deltaTime, 0));
	}
}
void Map::SpawnEnemies(sf::RenderWindow *window, float deltaTime)
{
	if (spawnEnemy01 >= spawnEnemy01Value)
	{
		bool isValid = false;
		float randomX;
		float randomY;
		while (!isValid)
		{
			randomX = rand() * window->getSize().x / (float)RAND_MAX;
			randomY = rand() * window->getSize().y / (float)RAND_MAX;
			float distance = Magnitude(player->playerShape.getPosition(), {randomX, randomY});
			isValid = distance < 1200;
		}
		auto testEnemy = new Enemy("Enemy", sf::Vector2f(randomX, randomY), Enemy::Type::Triangle);
		isValid = false;
		spawnEnemy01 = 0;
	}
	if (spawnEnemy01 < spawnEnemy01Value)
	{
		spawnEnemy01 += deltaTime;
	}
	if (spawnEnemy02 >= spawnEnemy02Value)
	{
		bool isValid = false;
		float randomX;
		float randomY;
		while (!isValid)
		{
			randomX = rand() * window->getSize().x / (float)RAND_MAX;
			randomY = rand() * window->getSize().y / (float)RAND_MAX;
			float distance = Magnitude(player->playerShape.getPosition(), {randomX, randomY});
			isValid = distance < 900;
		}
		auto testEnemy = new Enemy("Enemy", sf::Vector2f(randomX, randomY), Enemy::Type::Square);
		isValid = false;
		spawnEnemy02 = 0;
	}
	if (spawnEnemy02 < spawnEnemy02Value)
	{
		spawnEnemy02 += deltaTime;
	}
	if (spawnEnemy03 >= spawnEnemy03Value)
	{
		bool isValid = false;
		float randomX;
		float randomY;
		while (!isValid)
		{
			randomX = rand() * window->getSize().x / (float)RAND_MAX;
			randomY = rand() * window->getSize().y / (float)RAND_MAX;
			float distance = Magnitude(player->playerShape.getPosition(), {randomX, randomY});
			isValid = distance < 900;
		}
		auto testEnemy = new Enemy("Enemy", sf::Vector2f(randomX, randomY), Enemy::Type::Circle);
		isValid = false;
		spawnEnemy03 = 0;
	}
	if (spawnEnemy03 < spawnEnemy03Value)
	{
		spawnEnemy03 += deltaTime;
	}
	if (compteurEnemy <= 0)
	{
		bool isValid = false;
		float randomX;
		float randomY;
		while (!isValid)
		{
			randomX = rand() * window->getSize().x / (float)RAND_MAX;
			randomY = rand() * window->getSize().y / (float)RAND_MAX;
			float distance = Magnitude(player->playerShape.getPosition(), {randomX, randomY});
			isValid = distance < 800;
		}
		auto testEnemy = new Enemy("Enemy", sf::Vector2f(randomX, randomY), Enemy::Type::Octagon);
		isValid = false;
		compteurEnemy = compteurEnemyValue;
	}
}