#include "Bonus.h"
Bonus::~Bonus()
{
	LOG("destroy Bonus");
}
Bonus::Bonus(sf::Vector2f pos, TypeBonus type, std::string id)
{
	// this->id = id;
	form.setPointCount(5);
	form.setRadius(15.0f);
	form.setPosition(pos);
	this->type = type;
	if (type == TypeBonus::HEALTH)
	{
		form.setFillColor(sf::Color::Green);
	}
	else
	{
		form.setFillColor(sf::Color::Yellow);
	}
}
void Bonus::Update(sf::RenderWindow *window, float deltaTime)
{
	sf::Vector2f dirPlay = Player::player->playerShape.getPosition() - form.getPosition();
	float magPlay = sqrt(powf(dirPlay.x, 2) + powf(dirPlay.y, 2));
	if (magPlay < (form.getRadius() + Player::player->playerShape.getRadius()) && type == TypeBonus::HEALTH)
	{
		Player::player->lifeP += amount;
		if (Player::player->lifeP > Player::player->lifeMax)
		{
			Player::player->lifeP = Player::player->lifeMax;
		}
		DestroyObject2(this);
	}
	else if (magPlay < (form.getRadius() + Player::player->playerShape.getRadius()) && type == TypeBonus::NUKE)
	{
		Player::player->bonusDuration = duration;
		DestroyObject2(this);
	}
	window->draw(form);
}