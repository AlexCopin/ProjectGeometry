#include <time.h>
#include <math.h>
#include "MathUtils.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
Enemy::Enemy(std::string id, sf::Vector2f position, Type type)
{
	map = (Map *)FindObject("Map");
	this->id = id;
	this->type = type;
	this->position = position;
	switch (type)
	{
	case Type::Triangle:
		health = 100;
		speed = 200;
		// Appearance
		shape.setPointCount(3);
		shape.setScale(.8, 1);
		color = sf::Color::Red;
		radius = 15;
		break;
	case Type::Square:
		health = 200;
		speed = 100;
		// Appearance
		shape.setPointCount(4);
		color = sf::Color::Blue;
		radius = 30;
		// Target
		srand(time(0));
		patrolTime = 1 + (rand() % 9);
		break;
	case Type::Circle:
		health = 400;
		speed = 60;
		// Appearance
		color = sf::Color::Yellow;
		radius = 30;
		break;
	case Type::Octagon:
		health = 1000;
		speed = 20;
		// Appearance
		shape.setPointCount(8);
		color = sf::Color::Green;
		radius = 100;
		break;
	}
	shape.setPosition(position);
	// Appearance
	shape.setFillColor(color);
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	// Player
	player = (Player *)FindObject("Player");
}
void Enemy::Update(sf::RenderWindow *window, float deltaTime)
{
	switch (type)
	{
	case Type::Triangle:
	{
		// Target
		target = player->posPlayer;
		// Position
		sf::Vector2f direction = target - shape.getPosition();
		float distance = sqrt(powf(direction.x, 2) + powf(direction.y, 2));
		sf::Vector2f dirNorm = direction / distance;
		shape.setPosition(shape.getPosition() + dirNorm * speed * deltaTime);
		// Rotation
		float angle = atan2f(direction.y, direction.x);
		shape.setRotation(ConvertRadToDeg(angle + IIM_PI / 2));
	}
	break;
	case Type::Square:
	{
		timer -= deltaTime;
		if (timer <= 0)
		{
			isOnTarget *= -1;
			timer = patrolTime;
		}
		// Target
		target = isDirVert ? sf::Vector2f(position.x, position.y + window->getSize().y) : sf::Vector2f(position.x + window->getSize().x, position.y);
		// Position
		sf::Vector2f direction = target - shape.getPosition();
		float distance = sqrt(powf(direction.x, 2) + powf(direction.y, 2));
		sf::Vector2f dirNorm = direction / distance;
		shape.setPosition(shape.getPosition() + dirNorm * isOnTarget * speed * deltaTime);
		// Rotation
		shape.setRotation(45);
	}
	break;
	case Type::Circle:
	{
		// Position
		sf::Time elapsed = clock.getElapsedTime();
		sf::Vector2f direction(speed * deltaTime, sin(elapsed.asSeconds()) * amplitude);
		shape.setPosition(shape.getPosition() + direction);
	}
	break;
	}
	// Draw
	window->draw(shape);
	// Health
	if (health <= 0)
		delete this;
}