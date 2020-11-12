#include "Bullet.h"

Bullet::Bullet(int damage,  sf::Vector2f mousePos)
{
	Player* player = (Player*)FindObject("Player");
	timeInSeconds = 2.0f; 
	std::size_t count = 0;
	if (player->typeWeapon == Player::TYPEBULLET::STICK)
	{
		count = 2;
	}
	else if (player->typeWeapon == Player::TYPEBULLET::TRIANGLE)
	{
		count = 3;
	}
	else if (player->typeWeapon == Player::TYPEBULLET::SQUARE)
	{
		count = 4;
	}
	else if (player->typeWeapon == Player::TYPEBULLET::PENTAGONE)
	{
		count = 5;
	}
	else if (player->typeWeapon == Player::TYPEBULLET::HEXAGONE)
	{
		count = 6;
	}

	originPos = player->posPlayer;
	targetPos = mousePos;
	damageB = damage;
	speedB = 0.000001f;
	shapeB.setPointCount(count);
	//shapeB.setOrigin(player->posPlayer);
	shapeB.setPosition(player->posPlayer);
	shapeB.setFillColor(sf::Color::Red);
	shapeB.setRadius(20.0f);
}
void Bullet::Update(sf::RenderWindow* window, float deltaTime)
{
	sf::Vector2f trajectoireBullet = targetPos - originPos;
	sf::Clock clockG;
	timeInSeconds -= deltaTime;
	shapeB.setPosition(trajectoireBullet.x + (deltaTime * speedB), trajectoireBullet.y + (deltaTime * speedB));
	//LOG(timeInSeconds);
	if (timeInSeconds <= 0.0f) 
	{
		DestroyObject(this);
		timeInSeconds = 2.0f;
	}
	window->draw(shapeB);
}

