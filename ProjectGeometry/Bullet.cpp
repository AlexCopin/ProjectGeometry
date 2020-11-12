#include "Bullet.h"

void Bullet::Update(sf::RenderWindow* window, float deltaTime)
{
	sf::Mouse mouse;
	sf::Vector2i posMouseInt;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		posMouseInt = mouse.getPosition(*window);
	}
	sf::Vector2f posMouse(posMouseInt);
	sf::Vector2f originPosBullet(originPosX,originPosY);
	sf::Vector2f trajectoireBullet = posMouse - originPosBullet;
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	shapeB.setPosition(trajectoireBullet.x * (timeInSeconds * speedB), trajectoireBullet.y * (timeInSeconds * speedB));
	if (timeInSeconds > 3.0f) {
		DestroyObject(this);
	}
	LOG("Bullet existante");
	window->draw(shapeB);
}

