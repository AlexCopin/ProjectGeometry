#pragma once
#include "Main.h"
#include "Map.h"
#include "Background.h"
#include "Player.h"

class UI : Object
{
public:
	UI(std::string id, sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float DeltaTime);
	void DrawPlayerHealth(sf::RenderWindow* window);
	void GameOver(sf::RenderWindow* window);
	void GameStart(sf::RenderWindow* window);
	void Score(sf::RenderWindow* window);
	sf::Font GetFont();
};