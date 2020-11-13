#include "Map.h"
#include "Enemy.h"
#include "Ship.h"

Map::Map(std::string id, sf::RenderWindow *window)
{

	this->id = "Map";
	limitUP.setFillColor(sf::Color::Yellow);
	limitUP.setSize(sf::Vector2f(1000, 100));
	limitUP.setPosition(sf::Vector2f(0, -90));

	limitDOWN.setFillColor(sf::Color::Yellow);
	limitDOWN.setSize(sf::Vector2f(1000, 100));
	limitDOWN.setPosition(sf::Vector2f(0, 590));

	limitRIGHT.setFillColor(sf::Color::Yellow);
	limitRIGHT.setSize(sf::Vector2f(100, 600));
	limitRIGHT.setPosition(sf::Vector2f(-90, 0));

	limitLEFT.setFillColor(sf::Color::Yellow);
	limitLEFT.setSize(sf::Vector2f(100, 600));
	limitLEFT.setPosition(sf::Vector2f(990, 0));

	player = new Player("Player", 1, 0.2f, 50, 50);

	auto shipTest = new Ship(sf::Vector2f(window->getSize().x / 1.5f, window->getSize().y / 2.0f), "ship1");
	auto shipTest1 = new Ship(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f), "ship2");
	auto shipTest2 = new Ship(sf::Vector2f(window->getSize().x / 2.5f, window->getSize().y / 2.5f), "ship2");
	auto shipTest3 = new Ship(sf::Vector2f(window->getSize().x / 1.5f, window->getSize().y / 1.5f), "ship2");
	auto shipTest4 = new Ship(sf::Vector2f(window->getSize().x / 1.8f, window->getSize().y / 2.5f), "ship2");

	// Julien: testEnemy
	auto testEnemy = new Enemy("testEnemy", sf::Vector2f(), Enemy::Type::Triangle);
}

void Map::Update(sf::RenderWindow *window, float deltaTime)
{

	CollisionPlayer();

	window->draw(limitUP);
	window->draw(limitDOWN);
	window->draw(limitRIGHT);
	window->draw(limitLEFT);
}

void Map::CollisionPlayer()
{
	if (limitUP.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(0, -1));
	}
	else if (limitDOWN.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(0, 1));
	}

	if (limitRIGHT.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(-1, 0));
	}
	else if (limitLEFT.getGlobalBounds().intersects(player->playerShape.getGlobalBounds()))
	{
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(1, 0));
	}
}