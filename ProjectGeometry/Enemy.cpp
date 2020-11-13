#include "Enemy.h"
#include "Player.h"
Enemy::Enemy(std::string id, sf::Vector2f position, Type type)
{
	this->id = id;
	this->position = position;
	switch (type)
	{
	case Type::Triangle:
		shape.setPointCount(3);
		shape.setRadius(50);
		health = 100;
		speed = 50;
		break;
	case Type::Square:
		shape.setPointCount(4);
		shape.setRadius(50);
		health = 200;
		speed = 30;
		break;
	case Type::Octagon:
		shape.setPointCount(8);
		shape.setRadius(50);
		health = 400;
		speed = 20;
		break;
	case Type::Circle:
		shape.setRadius(100);
		health = 1000;
		speed = 10;
		break;
	}
	player = (Player *)FindObject("Player");
}
void Enemy::Update(sf::RenderWindow *window, float deltaTime)
{
	// sf::Vector2f target = targetPos - originPos;
	// timeInSeconds -= deltaTime;
	// shapeB.setPosition(trajectoireBullet.x + (deltaTime * speedB), trajectoireBullet.y + (deltaTime * speedB));
	// window->draw(shape);
}