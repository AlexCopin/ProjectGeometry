#include "Menu.h"
Menu::Menu(sf::RenderWindow &window)
{
	if (!font.loadFromFile(getAssetsPath() + "\\spaceAge.ttf"))
	{
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::White);
	menu[0].setString("Space Wahou");
	menu[0].setPosition(sf::Vector2f(window.getSize().x / 2 - ((menu[0].getCharacterSize() * menu[0].getString().getSize()) / 2), window.getSize().y / 4 * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Cyan);
	menu[1].setString("Play");
	menu[1].setPosition(sf::Vector2f(window.getSize().x / 2 - ((menu[1].getCharacterSize() * menu[1].getString().getSize()) / 2), window.getSize().y / 4 * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Quit");
	menu[2].setPosition(sf::Vector2f(window.getSize().x / 2 - ((menu[2].getCharacterSize() * menu[2].getString().getSize()) / 2), window.getSize().y / 4 * 3));
	selectedItemIndex = 1;
}
Menu::~Menu()
{
}
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 1)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
	}
}
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
	}
}
void Menu::OnEventMenu(sf::RenderWindow *window, sf::Event event, float deltaTime)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			MoveUp();
			break;
		case sf::Keyboard::Down:
			MoveDown();
			break;
		case sf::Keyboard::Enter:
			switch (GetPressedItem())
			{
			case 1:
				gameLaunched = true;
				isPaused = false;
				break;
			case 2:
				window->close();
				break;
			}
		}
		break;
	}
}
void Menu::drawMenu(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}