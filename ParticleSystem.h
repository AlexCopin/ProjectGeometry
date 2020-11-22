#pragma once
#include "Main.h"
#include <list>

class ParticleSystem: public Object2
{
public:
	float duration;
	std::list<sf::RectangleShape*> points;
	int count;
	ParticleSystem(int count, float duration, sf::Vector2f position, sf::Color color, sf::Vector2f size);
	sf::Color color;
	void Update(sf::RenderWindow* window, float deltaTime);
	void MoveParticles(float deltaTime);
	void DrawParticles(sf::RenderWindow* window);
	void DestroyParticles();
};