#pragma once
#include "Main.h"
#include "Map.h"
#include "Background.h"
#include "Player.h"
class UI :public Object
{
public:
	sf::Font policeUI;
	bool loser = false;
	UI(std::string id, sf::RenderWindow *window, sf::Font font);
	void Update(sf::RenderWindow *window, float deltaTime);
	void DrawPlayerHealth(sf::RenderWindow *window);
	void GameOver(sf::RenderWindow *window);
	void Score(sf::RenderWindow *window);
};