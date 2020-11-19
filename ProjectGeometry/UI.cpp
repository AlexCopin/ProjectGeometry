#include "UI.h"

UI::UI(std::string id, sf::RenderWindow* window,sf::Font font)
{
	this->id = id;
	policeUI = font;
}

void UI::Update(sf::RenderWindow* window, float deltaTime)
{
	DrawPlayerHealth(window);
	Score(window);
	GameOver(window);
}


void UI::DrawPlayerHealth(sf::RenderWindow* window)
{
	sf::Text playerHealth;
	playerHealth.setFont(policeUI);
	playerHealth.setString(std::to_string(Player::player->lifeP));
	playerHealth.setPosition(50, 50);
	window->draw(playerHealth);
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
	sf::Text textScore;
	textScore.setFont(policeUI);
	textScore.setString(std::to_string(Player::player->score));
	textScore.setPosition(window->getSize().x - 200, 50);
	window->draw(textScore);
}