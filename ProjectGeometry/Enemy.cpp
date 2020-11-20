#include <ctime>
#include <cmath>
#include "MathUtils.h"
#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
Enemy::Enemy(std::string id, sf::Vector2f position, Type type)
{
	srand(time(0));
	loot = rand() % 2;
	getEnemies().push_back(this);
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
		shape.setOutlineColor(sf::Color(96, 96, 96));
		shape.setOutlineThickness(2);
		shape.setScale(.8, 1);
		color = sf::Color(255, 255, 0);
		radius = 20;
	}
	break;
	case Type::Square:
	{
		health = 200;
		damage = 20;
		speed = 100;
		// Appearance
		shape.setPointCount(4);
		shape.setOutlineColor(sf::Color(96, 96, 96));
		color = sf::Color(255, 180, 0);
		shape.setOutlineThickness(2);
		radius = 30;
		// Target
		srand(time(0));
		patrolTime = 2 + (rand() % 10);
		// Rotation
		srand(time(0));
		isRot = rand() % 2;
		float rot = isRot ? 0 : 45;
		shape.setRotation(rot);
		// Bullet
		cadence = 1;
		bulCount = 4;
	}
	break;
	case Type::Circle:
	{
		health = 400;
		damage = 30;
		speed = 60;
		// Appearance
		shape.setOutlineColor(sf::Color(96, 96, 96));
		color = sf::Color(205, 51, 51);
		shape.setOutlineThickness(2);
		radius = 30;
		// Target
		srand(time(0));
		isDirVert = rand() % 2;
		patrolTime = 2 + (rand() % 10);
		// Bullet
		cadence = .5;
		bulCount = 32;
	}
	break;
	case Type::Octagon:
	{
		health = 800;
		damage = 60;
		speed = 20;
		// Appearance
		shape.setPointCount(8);
		radius = 80;
		shape.setOutlineColor(sf::Color(96, 96, 96));
		shape.setOutlineThickness(2);
		color = sf::Color(102, 0, 0);
		// Target
		srand(time(0));
		isDirVert = rand() % 2;
		patrolTime = 1 + (rand() % 5);
		// Bullet
		cadence = .5;
		bulCount = 8;
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
Enemy::~Enemy()
{
	getEnemies().erase(std::find(getEnemies().begin(), getEnemies().end(), this));
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
		// Bullet
		if (shape.getRotation() == 45)
		{
			sf::Vector2f dir1 = sf::Vector2f(-1, 0);
			float bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			sf::Vector2f dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
			//
			dir1 = sf::Vector2f(1, 0);
			bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
			//
			dir1 = sf::Vector2f(0, -1);
			bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
			//
			dir1 = sf::Vector2f(0, 1);
			bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
		}
		else
		{
			sf::Vector2f dir1 = sf::Vector2f(-.5, .5);
			float bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			sf::Vector2f dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
			//
			dir1 = sf::Vector2f(.5, .5);
			bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
			//
			dir1 = sf::Vector2f(.5, -.5);
			bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
			//
			dir1 = sf::Vector2f(.5, .5);
			bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
			dir2 = dir1 / bulMag;
			ShootBul(deltaTime, dir2, 0);
		}
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
		sf::Vector2f dir1 = VectorNewAngle(shape.getRotation(), shape.getPosition());
		float bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		sf::Vector2f dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, shape.getRotation());
	}
	break;
	case Type::Octagon:
	{
		// Timer
		timer -= deltaTime;
		if (timer <= 0)
		{
			isOnTarget *= -1;
			timer = patrolTime;
		}
		// Rotation
		float rot = shape.getRotation();
		rot += isOnTarget == 1 ? .5 : -.5;
		shape.setRotation(rot);
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
		// Bullet
		sf::Vector2f dir1 = sf::Vector2f(-1, 0);
		float bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		sf::Vector2f dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(1, 0);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(0, -1);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(0, 1);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(-.5, .5);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(.5, .5);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(.5, -.5);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
		//
		dir1 = sf::Vector2f(.5, .5);
		bulMag = sqrt(powf(dir1.x, 2) + powf(dir1.y, 2));
		dir2 = dir1 / bulMag;
		ShootBul(deltaTime, dir2, 0);
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
		Map::mape->compteurEnemy--;
		player->lifeP -= damage * 2;
		health = 0;
		// player->ships.pop_back();
	}
	// Score
	score = damage * 10;
	// Health
	if (health <= 0)
	{
		player->score += score;
		getEnemies().erase(std::find(getEnemies().begin(), getEnemies().end(), this));
		DestroyObject(this);
		if (loot)
			new Ship(shape.getPosition(), "enemyLoot");
	}
}
void Enemy::ShootBul(float deltaTime, sf::Vector2f dir, float angle)
{
	timerBul -= deltaTime;
	if (timerBul <= 0)
	{
		auto bul = new Bullet(damage, dir, Bullet::Type::Enemy);
		bul->shapeB.setPosition(shape.getPosition());
		bul->shapeB.setRotation(ConvertRadToDeg(angle + IIM_PI / 2));
		bul->shapeB.setScale(.5, .5);
		bul->shapeB.setFillColor(color);
		bul->count = bulCount;
		timerBul = cadence;
	}
}