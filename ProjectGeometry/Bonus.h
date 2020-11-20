#pragma once
#include "Main.h"
#include "Player.h"
class Bonus : Object2
{
public:
	enum class TypeBonus
	{
		HEALTH,
		NUKE
	} type;
	sf::CircleShape form;
	float duration = 5.0f;
	int amount = 100;
	Bonus(sf::Vector2f pos, TypeBonus type, std::string id);
	void Update(sf::RenderWindow* window, float deltaTime);
};