#include "Map.h"

    Map::Map(std::string id) 
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

		

	}


void Map::Update(sf::RenderWindow* window, float deltaTime) {

	CollisionPlayer();

	window->draw(limitUP);
	window->draw(limitDOWN);
	window->draw(limitRIGHT);
	window->draw(limitLEFT);


}


void Map::CollisionPlayer() {
	if (limitUP.getGlobalBounds().intersects(player->playerShape.getGlobalBounds())) {
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(0, -1));
	} else if (limitDOWN.getGlobalBounds().intersects(player->playerShape.getGlobalBounds())) {
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(0, 1));
	}

	if (limitRIGHT.getGlobalBounds().intersects(player->playerShape.getGlobalBounds())) {
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(-1, 0));
	}
	else if (limitLEFT.getGlobalBounds().intersects(player->playerShape.getGlobalBounds())) {
		player->playerShape.setPosition(player->playerShape.getPosition() - sf::Vector2f(1, 0));
	}
}