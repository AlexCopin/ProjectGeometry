#pragma once
#include "Main.h"
#define MAX_NUMBER_OF_ITEMS 4
class Menu :public Object
{
public:
	Menu(sf::RenderWindow &window);
	~Menu();
	bool isPaused = false;
	bool gameLaunched = false;
	bool soundON = true;
	void drawMenu(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void OnEventMenu(sf::RenderWindow *window, sf::Event event, float deltaTime);
	int GetPressedItem() { return selectedItemIndex; };

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sound* soundplayer = getSoundPlayer();
	sf::Sound* soundenemy = getSoundEnemy();
	sf::Music* music1 = getMusic();
};