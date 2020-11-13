#include "Bullet.h"

Bullet::Bullet(int damage, sf::Vector2f direction, float speed)
{
	std::size_t count = 0;
	if (Player::player->typeWeapon == Player::TYPEBULLET::TRIANGLE)
	{
		count = 3;
	}
	else if (Player::player->typeWeapon == Player::TYPEBULLET::SQUARE)
	{
		count = 4;
	}
	else if (Player::player->typeWeapon == Player::TYPEBULLET::PENTAGONE)
	{
		count = 5;
	}
	else if (Player::player->typeWeapon == Player::TYPEBULLET::HEXAGONE)
	{
		count = 6;
	}
	damageB = damage;
	speedB = speed;
	trajectoire = direction;
	shapeB.setPointCount(count);
	shapeB.setFillColor(sf::Color::Red);
	shapeB.setRadius(20.0f);
}
void Bullet::Update(sf::RenderWindow* window, float deltaTime)
{
	MoveBullet();
	window->draw(shapeB);
}

void Bullet::MoveBullet()
{
	shapeB.setPosition(shapeB.getPosition() + trajectoire * 5.0f);
}