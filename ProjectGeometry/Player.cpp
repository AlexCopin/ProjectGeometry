#include "Player.h"
Player *Player::player = nullptr;
std::list<Bullet *> bullets;
std::list<Bullet *> &getBullets() { return bullets; }
Player::Player(std::string id, int life, int posX, int posY)
{
	this->id = "Player";
	lifeP = life;
	posX = posX;
	posY = posY;
	posPlayer = sf::Vector2f(posX, posY);
	playerShape.setPosition(posPlayer);
	playerShape.setRadius(50.0f);
	playerShape.setFillColor(sf::Color(192, 192, 192));
	playerShape.setOrigin(50, 50);
	playerShape.setPointCount(10);
	playerShape.setOutlineColor(sf::Color(90, 90, 90));
	playerShape.setOutlineThickness(3);
	shipsShape.setPosition(playerShape.getPosition());
	shipsShape.setRadius(70.0f);
	shipsShape.setPointCount(0);
	shipsShape.setFillColor(sf::Color::Transparent);
	shipsShape.setOutlineColor(sf::Color::Red);
	shipsShape.setOrigin(sf::Vector2f(70, 70));
	shipsShape.setOutlineThickness(3);
	typeB = TYPEBULLET::BASE;
	buffer_gun.loadFromFile(getAssetsPath() + "Sounds\\gun2.ogg");
	buffer_shotgun.loadFromFile(getAssetsPath() + "Sounds\\pompe3.ogg");
	buffer_rifle1.loadFromFile(getAssetsPath() + "Sounds\\Mitraillette1.ogg");
	buffer_rifle2.loadFromFile(getAssetsPath() + "Sounds\\Mitraillette2.ogg");
	buffer_rifle3.loadFromFile(getAssetsPath() + "Sounds\\Mitraillette3.ogg");
	buffer_rifle4.loadFromFile(getAssetsPath() + "Sounds\\Mitraillette4.ogg");
	buffer_rifleEnd.loadFromFile(getAssetsPath() + "Sounds\\Mitraillette_End.ogg");
	buffer_crazy.loadFromFile(getAssetsPath() + "Sounds\\crazy.ogg");
	music1.openFromFile(getAssetsPath() + "Sounds\\Musique Entiere.ogg");
	music2.openFromFile(getAssetsPath() + "Sounds\\MusicPart2.ogg");
	player = this;
	music1.play();
	music1.setLoop(true);
}
void Player::Update(sf::RenderWindow *window, float deltaTime)
{
	shieldFactor = int((int)ships.size() / 3);
	if (shieldFactor >= 50)
		shieldFactor = 50;

	bonusDuration -= deltaTime;
	if (bonusDuration > 0)
	{
		typeB = TYPEBULLET::BONUS;
	}
	else if (typeB == TYPEBULLET::BONUS && bonusDuration <= 0)
	{
		typeB = TYPEBULLET::BASE;
	}
	bool isOneKeyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// left key is pressed: move our character
		MovePlayer(-1, 0, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// left key is pressed: move our character
		MovePlayer(1, 0, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		// left key is pressed: move our character
		MovePlayer(0, -1, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// left key is pressed: move our character
		MovePlayer(0, 1, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (!isOneKeyPressed)
	{
		float magnitude = sqrt(powf(Movement.x, 2) + powf(Movement.y, 2));
		if (magnitude > 0)
		{
			float magnitude2 = magnitude - 600 * deltaTime;
			if (magnitude2 < 0)
			{
				magnitude2 = 0;
			}
			Movement = Movement / magnitude * magnitude2;
		}
	}
	playerShape.setPosition(playerShape.getPosition() + Movement * deltaTime);
	// DestroyBullet();
	ShootBullet(window, deltaTime);
	ShipShootBullet(window, deltaTime);
	posPlayer = playerShape.getPosition();
	MovementShipsShape(deltaTime);
	//ChangeWeapon();
	window->draw(playerShape);
	window->draw(shipsShape);
}
void Player::OnEvent(sf::RenderWindow *window, sf::Event event, float deltaTime)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
	{
		ChangeWeapon();
	}
}
void Player::ShootBullet(sf::RenderWindow *window, float deltaTime)
{
	//BULLET ALEX
	sf::Vector2f playerCenter = sf::Vector2f(playerShape.getPosition().x + playerShape.getRadius() / 4, playerShape.getPosition().y + playerShape.getRadius() / 4);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		isMouseButtonDown = true;
		if (shootTimer >= shootTimerValue) //Shoot
		{
			if (typeB == TYPEBULLET::SHOTGUN)
			{
				sound.setBuffer(buffer_shotgun);
				sound.play();
				Bullet *bullet = new Bullet(damageP, GetTraj(window, playerCenter), Bullet::Type::Player);
				bullet->shapeB.setPosition(playerCenter);
				Bullet *bullet2 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(20), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet2->shapeB.setPosition(playerCenter);
				Bullet *bullet3 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(-20), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet3->shapeB.setPosition(playerCenter);
				Bullet *bullet4 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(160), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet4->shapeB.setPosition(playerCenter);
				Bullet *bullet5 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(-160), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet5->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				bullets.push_back(bullet2);
				bullets.push_back(bullet3);
				bullets.push_back(bullet4);
				bullets.push_back(bullet5);
				shootTimer = 0;
			}
			else if (typeB == TYPEBULLET::MITRAILLETTE)
			{
				int i = rand() % 4 + 1;
				if (i == 1)
				{
					sound.setBuffer(buffer_rifle1);
					sound.play();
				}
				else if (i == 2)
				{
					sound.setBuffer(buffer_rifle2);
					sound.play();
				}
				else if (i == 3)
				{
					sound.setBuffer(buffer_rifle3);
					sound.play();
				}
				else if (i == 4)
				{
					sound.setBuffer(buffer_rifle4);
					sound.play();
				}
				Bullet *bullet = new Bullet(damageP, GetTraj(window, playerCenter), Bullet::Type::Player);
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				shootTimer = 0;
			}
			else if (typeB == TYPEBULLET::CRAZY)
			{
				sound.setBuffer(buffer_crazy);
				sound.play();
				float angle = 1 + (rand() % 360);
				Bullet *bullet = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				float angle2 = 1 + (rand() % 360);
				Bullet *bullet2 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle2), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet2->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet2);
				shootTimer = 0;
			}
			else if (typeB == TYPEBULLET::BONUS)
			{
				float angle = 1 + (rand() % 360);
				Bullet *bullet = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle), GetTraj(window, playerCenter)), Bullet::Type::Player);
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
			}
			else
			{
				sound.setBuffer(buffer_gun);
				sound.play();
				Bullet *bullet = new Bullet(damageP, GetTraj(window, playerCenter), Bullet::Type::Player);
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				shootTimer = 0;
			}
		}
	}
	else
	{
		if (isMouseButtonDown)
		{
			isMouseButtonDown = false;
			if (typeB == TYPEBULLET::MITRAILLETTE)
			{
				sound.setBuffer(buffer_rifleEnd);
				sound.play();
			}
		}
	}
	if (shootTimer < shootTimerValue)
	{
		shootTimer += deltaTime;
	}
}
void Player::ShipShootBullet(sf::RenderWindow *window, float deltaTime)
{
	//BULLET ALEX
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (shootTimerShip >= shootTimerShipValue) //Shoot
		{
			std::list<Ship *>::iterator ite = ships.begin();
			while (ite != ships.end())
			{
				sf::Vector2f trajectoireBullet = GetTraj(window, (*ite)->shipShape.getPosition());
				if (typeB == TYPEBULLET::SHOTGUN)
				{
					Bullet *bullet = new Bullet(damageShip, trajectoireBullet, Bullet::Type::Player);
					bullet->shapeB.setPosition((*ite)->shipShape.getPosition());
					Bullet *bullet4 = new Bullet(damageShip, VectorNewAngle(ConvertRadToDeg(160), trajectoireBullet), Bullet::Type::Player);
					bullet4->shapeB.setPosition((*ite)->shipShape.getPosition());
					Bullet *bullet5 = new Bullet(damageShip, VectorNewAngle(ConvertRadToDeg(-160), trajectoireBullet), Bullet::Type::Player);
					bullet5->shapeB.setPosition((*ite)->shipShape.getPosition());
					bullet->shapeB.setRadius(bullet->shapeB.getRadius() / 2);
					bullet4->shapeB.setRadius(bullet4->shapeB.getRadius() / 2);
					bullet5->shapeB.setRadius(bullet5->shapeB.getRadius() / 2);
					bullet->shapeB.setFillColor(sf::Color::Cyan);
					bullet4->shapeB.setFillColor(sf::Color::Cyan);
					bullet5->shapeB.setFillColor(sf::Color::Cyan);
					bullets.push_back(bullet);
					bullets.push_back(bullet4);
					bullets.push_back(bullet5);
					shootTimerShip = 0;
				}
				else if (typeB == TYPEBULLET::CRAZY)
				{
					float angle = 1 + (rand() % 360);
					Bullet *bullet = new Bullet(damageShip, VectorNewAngle(ConvertRadToDeg(angle), trajectoireBullet), Bullet::Type::Player);
					bullet->shapeB.setPosition((*ite)->shipShape.getPosition());
					float angle2 = 1 + (rand() % 360);
					Bullet *bullet2 = new Bullet(damageShip, VectorNewAngle(ConvertRadToDeg(angle2), trajectoireBullet), Bullet::Type::Player);
					bullet2->shapeB.setPosition((*ite)->shipShape.getPosition());
					bullet->shapeB.setRadius(bullet->shapeB.getRadius() / 2);
					bullet2->shapeB.setRadius(bullet2->shapeB.getRadius() / 2);
					bullet->shapeB.setFillColor(sf::Color::Cyan);
					bullet2->shapeB.setFillColor(sf::Color::Cyan);
					bullets.push_back(bullet);
					bullets.push_back(bullet2);
					shootTimerShip = 0;
				}
				else if (typeB == TYPEBULLET::BONUS)
				{
					float angle = 1 + (rand() % 360);
					Bullet *bullet = new Bullet(damageShip, VectorNewAngle(ConvertRadToDeg(angle), trajectoireBullet), Bullet::Type::Player);
					bullet->shapeB.setPosition((*ite)->shipShape.getPosition());
					bullet->shapeB.setRadius(bullet->shapeB.getRadius() / 2);
					bullet->shapeB.setFillColor(sf::Color::Cyan);
					bullets.push_back(bullet);
					shootTimerShip = 0;
				}
				else
				{
					Bullet *bullet = new Bullet(damageShip, trajectoireBullet, Bullet::Type::Player);
					bullet->shapeB.setPosition((*ite)->shipShape.getPosition());
					bullet->shapeB.setRadius(bullet->shapeB.getRadius() / 2);
					bullet->shapeB.setFillColor(sf::Color::Cyan);
					bullets.push_back(bullet);
					shootTimerShip = 0;
				}
				ite++;
			}
		}
	}
	if (shootTimerShip < shootTimerShipValue)
	{
		shootTimerShip += deltaTime;
	}
}
void Player::MovePlayer(float x, float y, float speed, float deltaTime)
{
	actualSpeed = speed;
	sf::Vector2f direction{x, y};
	Movement += direction * (float)1000 * deltaTime;
	float magnitude = sqrt(powf(Movement.x, 2) + powf(Movement.y, 2));
	if (magnitude > speed)
	{
		Movement = Movement / magnitude * speed;
	}
	return;
}
void Player::RotatePlayer(sf::RenderWindow *window)
{
	sf::Vector2i cursor = sf::Mouse::getPosition((*window));
	sf::Vector2f direction = sf::Vector2f(cursor.x, cursor.y) - playerShape.getPosition();
}
float Player::GetTime()
{
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	return timeInSeconds;
}
void Player::MovementShipsShape(float deltaTime)
{
	shipsShape.setPosition(playerShape.getPosition());
	shipsShapeAngle += 10.0f * deltaTime;
	shipsShape.setRotation(shipsShapeAngle);
	sf::Transform matrix = shipsShape.getTransform();
	std::list<Ship *>::iterator it = ships.begin();
	int i = 0;
	while (it != ships.end())
	{
		sf::Vector2f direction2 = matrix.transformPoint(shipsShape.getPoint(i)) - (*it)->posShip;
		float distance = sqrt(powf(direction2.x, 2) + powf(direction2.y, 2));
		if (distance > 0.1f)
		{
			direction2 = direction2 / distance;
			(*it)->posShip = (*it)->posShip + direction2 * (float)(i % 3 + 3) * distance * deltaTime;
		}
		it++;
		i++;
	}
}
void Player::GetShip(Ship *ship)
{
	sf::Transform matrix = shipsShape.getTransform();
	shipsShape.setPointCount(shipsShape.getPointCount() + 1);
	ship->posShip = matrix.transformPoint(shipsShape.getPoint(shipsShape.getPointCount() - 1));
	ships.push_back(ship);
}
void Player::TakeDamage(int damages)
{
	lifeP -= damages / ((shieldFactor > 0) ? shieldFactor : 1);
	if (ships.size() > 0)
	{
		shipsShape.setPointCount(shipsShape.getPointCount() - 1);
		DestroyObject2(ships.back());
		ships.pop_back();
	}
	if (lifeP <= 0)
	{
		PlayerDeath();
	}
}
void Player::PlayerDeath()
{
	// DestroyObject(this);
}
sf::Vector2f Player::GetTraj(sf::RenderWindow *window, sf::Vector2f pos)
{
	sf::Vector2i mousePosInt = mouse.getPosition(*window);
	sf::Vector2f mousePos(mousePosInt);
	sf::Vector2f trajectoireBullet = (mousePos - pos);
	return Normalized(trajectoireBullet);
}
void Player::ChangeWeapon()
{
	int newType = (int)typeB + 1;
	if (newType == (int)TYPEBULLET::SIZE || (newType == (int)TYPEBULLET::BONUS && bonusDuration <= 0))
	{
		newType = 0;
	}
	typeB = (TYPEBULLET)newType;
}
void Player::GameOver(sf::RenderWindow *window)
{
}