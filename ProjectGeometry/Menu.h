#pragma once
#include "Main.h"

#define MAX_NUMBER_OF_ITEMS 3

class Menu : Object
{
public:
	Menu(sf::RenderWindow& window);
	~Menu();

	bool gameLaunched = false;
	void drawMenu(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void OnEventMenu(sf::RenderWindow* window, sf::Event event, float deltaTime);
	int GetPressedItem() { return selectedItemIndex; };
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};