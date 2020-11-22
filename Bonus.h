#pragma once
#include "Main.h"
#include "Player.h"
class Bonus : public Object2
{
public:
	enum class TypeBonus
	{
		HEALTH,
		NUKE
	} type;
	sf::CircleShape form;
	float duration = 3.0f;
	int amount = 100;
	Bonus(sf::Vector2f pos, TypeBonus type, std::string id);
	~Bonus();
	void Update(sf::RenderWindow *window, float deltaTime);
};