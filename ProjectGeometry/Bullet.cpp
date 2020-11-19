#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
std::vector<Enemy*> enemiesB;
Bullet::Bullet(float damage, sf::Vector2f direction, Type type) : type(type)
{
	enemiesB = getEnemies();
	this->type = type;
	sf::Color color;
	std::size_t count = 0;
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
		Player::player->shootTimerValue = 0.1f;
		Player::player->shootTimerShipValue = 0.3f;
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
	damageB = damage;
	trajectoire = direction;
	shapeB.setPointCount(count);
	shapeB.setFillColor(color);
	shapeB.setRadius(radiusB);
	shapeB.setScale(scaleB, 1.0f);
	float aimingAngle = atan2f(direction.y, direction.x);
	shapeB.setRotation(ConvertRadToDeg(aimingAngle + IIM_PI / 2.0f));
	player = Player::player;
}
void Bullet::Update(sf::RenderWindow* window, float deltaTime)
{
	MoveBullet(speedB * deltaTime);
	window->draw(shapeB);
	// Destroy
	if (shapeB.getPosition().y < 0 || shapeB.getPosition().x < 0 || shapeB.getPosition().y > 1500 || shapeB.getPosition().x > 2500)
		DestroyObject2(this);
	// Player
	if (type == Type::Player)
	{
		for (auto enemy : enemiesB)
		{
			LOG(enemy->health);
			sf::Vector2f dir = enemy->shape.getPosition() - shapeB.getPosition();
			float mag = sqrt(powf(dir.x, 2) + powf(dir.y, 2));
			if (mag < shapeB.getRadius() + enemy->shape.getRadius())
				enemy->health -= damageB;
		}
	}
	// Enemy
	else if (type == Type::Enemy)
	{
		sf::Vector2f dirPlay = player->playerShape.getPosition() - shapeB.getPosition();
		float magPlay = sqrt(powf(dirPlay.x, 2) + powf(dirPlay.y, 2));
		if (magPlay < shapeB.getRadius() + player->playerShape.getRadius())
		{
			player->lifeP -= damageB;
			DestroyObject2(this);
		}
	}
}
void Bullet::MoveBullet(float speed)
{
	shapeB.setPosition(shapeB.getPosition() + trajectoire * speed);
}
