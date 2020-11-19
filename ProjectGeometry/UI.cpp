#include "UI.h"

UI::UI(std::string id, sf::RenderWindow* window)
{
	this->id = id;
}

void UI::Update(sf::RenderWindow* window, float DeltaTime)
{
	DrawPlayerHealth(window);
	Score(window);
	GameOver(window);
}


void UI::DrawPlayerHealth(sf::RenderWindow* window)
{
	sf::Text playerHealth;
}

void UI::GameOver(sf::RenderWindow* window)
{

	if (Player::player->lifeP < 0)
	{
		//DrawGameOver();
	}
}

void UI::GameStart(sf::RenderWindow* window)
{

}

void UI::Score(sf::RenderWindow* window)
{

}

sf::Font UI::GetFont()
{
	sf::Font police;
	police.loadFromFile(getAssetsPath() + "\\arial.ttf");
	return police;
}