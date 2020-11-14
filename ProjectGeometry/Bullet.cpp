#include "Bullet.h"

Bullet::Bullet(int damage, sf::Vector2f direction)
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
	trajectoire = direction;
	shapeB.setPointCount(count);
	shapeB.setFillColor(sf::Color::Red);
	shapeB.setRadius(radiusB);
	shapeB.setScale(scaleB, 1.0f);
	float aimingAngle = atan2f(direction.y, direction.x);
	shapeB.setRotation(ConvertRadToDeg(aimingAngle + IIM_PI / 2.0f));
}
void Bullet::Update(sf::RenderWindow* window, float deltaTime)
{
	MoveBullet(speedB * deltaTime);
	window->draw(shapeB);
}

void Bullet::MoveBullet(float speed)
{
	shapeB.setPosition(shapeB.getPosition() + trajectoire * speed);
	LOG(speed);
}