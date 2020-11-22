#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
Bullet::~Bullet()
{
	LOG("destroy Bullet");
}
Bullet::Bullet(float damage, sf::Vector2f direction, Type type) : type(type)
{
	this->type = type;
	damageB = damage;
	sf::Color color;
	if (Player::player->typeB == Player::TYPEBULLET::BASE)
	{
		count = 3;
		color = sf::Color::Red;
		Player::player->shootTimerValue = 0.5f;
		Player::player->shootTimerShipValue = 0.5f;
	}
	else if (Player::player->typeB == Player::TYPEBULLET::SHOTGUN)
	{
		Player::player->shootTimerValue = 1.0f;
		Player::player->shootTimerShipValue = 0.5f;
		color = sf::Color::Magenta;
		count = 4;
	}
	else if (Player::player->typeB == Player::TYPEBULLET::MITRAILLETTE)
	{
		Player::player->shootTimerValue = 0.15f;
		Player::player->shootTimerShipValue = 0.3f;
		damageB = damage / 3;
		color = sf::Color::Blue;
		scaleB = 0.5f;
		count = 5;
	}
	else if (Player::player->typeB == Player::TYPEBULLET::CRAZY)
	{
		Player::player->shootTimerValue = 0.2f;
		Player::player->shootTimerShipValue = 0.5f;
		color = sf::Color::Yellow;
		scaleB = 0.8f;
		count = 6;
	}
	else if (Player::player->typeB == Player::TYPEBULLET::BONUS)
	{
		Player::player->shootTimerValue = 0.1f;
		Player::player->shootTimerShipValue = 0.1f;
		color = sf::Color::Yellow;
		scaleB = 1.0f;
		count = 5;
	}
	trajectoire = direction;
	shapeB.setFillColor(color);
	shapeB.setRadius(radiusB);
	shapeB.setScale(scaleB, 1.0f);
	float aimingAngle = atan2f(direction.y, direction.x);
	shapeB.setRotation(ConvertRadToDeg(aimingAngle + IIM_PI / 2.0f));
	//player = Player::player;
}
void Bullet::Update(sf::RenderWindow *window, float deltaTime)
{
	playerShips = Player::player->ships.size();
	shapeB.setPointCount(count);
	MoveBullet(speedB * deltaTime);
	window->draw(shapeB);
	// Player
	if (type == Type::Player)
	{
		if (shapeB.getPosition().y < 0 || shapeB.getPosition().x < 0 || shapeB.getPosition().y > window->getSize().y || shapeB.getPosition().x > window->getSize().x)
		{
			LOG(3 << "=" << this);
			DestroyObject2(this);
		}
		else
		{
			for (auto enemy : getEnemies())
			{
				sf::Vector2f dir = enemy->shape.getPosition() - shapeB.getPosition();
				float mag = sqrt(powf(dir.x, 2) + powf(dir.y, 2));
				if (mag < shapeB.getRadius() + enemy->shape.getRadius())
				{
					enemy->health -= damageB;
					LOG(4 << "=" << this);
					DestroyObject2(this);
				}
			}
		}
	}
	// Enemy
	else if (type == Type::Enemy)
	{
		if (shapeB.getPosition().y < 0 || shapeB.getPosition().x < 0 || shapeB.getPosition().y > 1500 || shapeB.getPosition().x > 2500)
		{
			LOG(1 << "=" << this);
			DestroyObject2(this);
		}
		sf::Vector2f dirPlay = Player::player->playerShape.getPosition() - shapeB.getPosition();
		float magPlay = sqrt(powf(dirPlay.x, 2) + powf(dirPlay.y, 2));
		if (magPlay < shapeB.getRadius() + Player::player->playerShape.getRadius())
		{
			Player::player->lifeP -= damageB / ((Player::player->shieldFactor > 0) ? Player::player->shieldFactor : 1);
			LOG(2 << "=" << this);
			DestroyObject2(this);
		}
	}
}
void Bullet::MoveBullet(float speed)
{
	shapeB.setPosition(shapeB.getPosition() + trajectoire * speed);
}