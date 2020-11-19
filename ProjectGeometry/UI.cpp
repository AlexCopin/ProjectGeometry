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
	if (Player::player->lifeP < 0)
	{
		loser = true;
	}
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
	sf::Text gameOver;
	gameOver.setFont(policeUI);
	gameOver.setString("GAME OVER");
	gameOver.setPosition(window->getSize().x /2 - ((gameOver.getCharacterSize() * gameOver.getString().getSize()) / 2), window->getSize().y / 2);
	window->draw(gameOver);
}
void UI::Score(sf::RenderWindow* window)
{
	sf::Text textScore;
	textScore.setFont(policeUI);
	textScore.setString(std::to_string(Player::player->score));
	textScore.setPosition(window->getSize().x - 200, 50);
	window->draw(textScore);
}