#include <ctime>
#include <cmath>
#include "MathUtils.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
std::list<Bullet *> enemyBullets;
Enemy::Enemy(std::string id, sf::Vector2f position, Type type)
{
	map = (Map *)FindObject("Map");
	this->id = id;
	this->type = type;
	this->position = position;
	switch (type)
	{
	case Type::Triangle:
	{
		health = 100;
		damage = 10;
		speed = 200;
		// Appearance
		shape.setPointCount(3);
		shape.setScale(.8, 1);
		color = sf::Color::Red;
		radius = 15;
	}
	break;
	case Type::Square:
	{
		health = 200;
		damage = 20;
		speed = 100;
		// Appearance
		shape.setPointCount(4);
		color = sf::Color::Blue;
		radius = 30;
		// Target
		srand(time(0));
		patrolTime = 1 + (rand() % 9);
		// Rotation
		srand(time(0));
		isRot = rand() % 2;
		float rot = isRot ? 0 : 45;
		shape.setRotation(rot);
	}
	break;
	case Type::Circle:
	{
		health = 400;
		damage = 30;
		speed = 60;
		// Appearance
		color = sf::Color::Yellow;
		radius = 30;
		// Target
		srand(time(0));
		patrolTime = 2 + (rand() % 10);
		// Bullet
		cadence = 1;
	}
	break;
	case Type::Octagon:
	{
		health = 1000;
		damage = 60;
		speed = 20;
		// Appearance
		shape.setPointCount(8);
		color = sf::Color::Green;
		radius = 100;
	}
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
		// Timer
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
	}
	break;
	case Type::Circle:
	{
		// Timer
		timer -= deltaTime;
		if (timer <= 0)
		{
			isOnTarget *= -1;
			timer = patrolTime;
		}
		// Target
		target = isDirVert ? sf::Vector2f(position.x, position.y + window->getSize().y) : sf::Vector2f(position.x + window->getSize().x, position.y);
		// PositionX
		sf::Vector2f direction = target - shape.getPosition();
		float distance = sqrt(powf(direction.x, 2) + powf(direction.y, 2));
		sf::Vector2f dirNorm = direction / distance;
		// PositionY
		sf::Time elapsed = clock.getElapsedTime();
		// Position
		shape.setPosition(shape.getPosition().x + dirNorm.x * isOnTarget * speed * deltaTime,
						  shape.getPosition().y + sin(elapsed.asSeconds()) * amplitude * speed * deltaTime);
		// Rotation
		float rot = shape.getRotation();
		rot++;
		shape.setRotation(rot);
		// Bullet
		sf::Vector2f dirBul = sf::Vector2f(0, -1) - shape.getPosition();
		float angleBul = atan2f(dirBul.y, dirBul.x);
		float bulMag = sqrt(powf(dirBul.x, 2) + powf(dirBul.y, 2));
		sf::Vector2f dirBulNorm = dirBul / bulMag;
		ShootBul(deltaTime, dirBulNorm, angleBul);
	}
	break;
	}
	// Draw
	window->draw(shape);
	// Player
	sf::Vector2f dirPlay = player->playerShape.getPosition() - shape.getPosition();
	float magPlay = sqrt(powf(dirPlay.x, 2) + powf(dirPlay.y, 2));
	if (magPlay < radius + player->playerShape.getRadius())
	{
		player->lifeP -= damage * 2;
		delete this;
	}
	// Health
	if (health <= 0)
		delete this;
}
void Enemy::ShootBul(float deltaTime, sf::Vector2f dir, float angle)
{
	timerBul -= deltaTime;
	if (timerBul <= 0)
	{
		auto bul = new Bullet(10, dir);
		bul->shapeB.setPosition(shape.getPosition());
		bul->shapeB.setRotation(ConvertRadToDeg(angle + IIM_PI / 2));
		enemyBullets.push_back(bul);
		// Destroy
		if (bul->shapeB.getPosition().y < 0 || bul->shapeB.getPosition().x < 0 || bul->shapeB.getPosition().y > 1500 || bul->shapeB.getPosition().x > 2500)
		{
			enemyBullets.erase(std::find(enemyBullets.begin(), enemyBullets.end(), bul));
			DestroyObject2(bul);
		}
		timerBul = cadence;
	}
}