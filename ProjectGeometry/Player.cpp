#include "Player.h"


Player* Player::player = nullptr;
std::list<Ship*> ships;
std::list<Bullet*> bullets;
Player::Player(std::string id, int life, int posX, int posY)
{
	this->id = "Player";
	lifeP = life;
	posX = posX;
	posY = posY;
	posPlayer = sf::Vector2f(posX, posY);
	//std::size_t count = 5;
	//playerShape.setPointCount(count);
	playerShape.setPosition(posPlayer);
	playerShape.setRadius(50.0f);
	playerShape.setFillColor(sf::Color::White);
	playerShape.setOrigin(50, 50);
	playerShape.setPointCount(10);
	shipsShape.setRadius(70.0f);
	shipsShape.setPointCount(0);
	shipsShape.setFillColor(sf::Color::Transparent);
	shipsShape.setOutlineColor(sf::Color::Red);
	shipsShape.setOrigin(sf::Vector2f(70, 70));
	shipsShape.setOutlineThickness(3);
	typeWeapon = TYPEBULLET::TRIANGLE;
	player = this;
}


void Player::Update(sf::RenderWindow *window, float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// left key is pressed: move our character
		MovePlayer("left", speedP * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// left key is pressed: move our character
		MovePlayer("right", speedP * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		// left key is pressed: move our character
		MovePlayer("up", speedP * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// left key is pressed: move our character
		MovePlayer("down", speedP * deltaTime);
	}
	
	DestroyBullet();
	posPlayer = playerShape.getPosition();
	MovementShipsShape();
	window->draw(playerShape);
	window->draw(shipsShape);
	/*std::list<Ship*>::iterator it = ships.begin();
	while (it != ships.end()) {
		window->draw((*it)->shipShape);
	}*/
	
}

void Player::ShootBullet(sf::RenderWindow* window, float deltaTime)
{
	//BULLET ALEX
	sf::Vector2f playerCenter = sf::Vector2f(posPlayer.x + playerShape.getRadius() / 4 , posPlayer.y + playerShape.getRadius() /4);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (shootTimer >= shootTimerValue) //Shoot
		{
			Bullet* bullet = new Bullet(damageP, GetTraj(window, playerCenter));
			bullet->shapeB.setPosition(playerCenter);
			bullets.push_back(bullet);
			shootTimer = 0;
		}
	}
	if (shootTimer < shootTimerValue)
	{
		shootTimer += deltaTime;
	}
}


void Player::ShipShootBullet(sf::RenderWindow* window, float deltaTime)
{
	//BULLET ALEX

	sf::Vector2f playerCenter = sf::Vector2f(posPlayer.x + playerShape.getRadius() / 4, posPlayer.y + playerShape.getRadius() / 4);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (shootTimer >= shootTimerValue) //Shoot
		{
			std::list<Ship*>::iterator ite = ships.begin();
			while (ite != ships.end())
			{
				sf::Vector2f trajectoireBullet = GetTraj(window, (*ite)->shipShape.getPosition());
				//sf::Vector2f trajectoireBullet = GetTraj(window, playerCenter);
				Bullet* bullet = new Bullet(damageP, trajectoireBullet);
				bullet->shapeB.setFillColor(sf::Color::Cyan);
				bullets.push_back(bullet);
				bullet->shapeB.setPosition((*ite)->shipShape.getPosition());
				ite++;
			}			
		}
	}
}
void Player::MovePlayer(std::string direction, float speed)
{
	if (direction == "up")
	{
		playerShape.setPosition(playerShape.getPosition().x, playerShape.getPosition().y - speed);
	}
	else if (direction == "right")
	{
		playerShape.setPosition(playerShape.getPosition().x + speed, playerShape.getPosition().y);
	}
	else if (direction == "down")
	{
		playerShape.setPosition(playerShape.getPosition().x, playerShape.getPosition().y + speed);
	}
	else if (direction == "left")
	{
		playerShape.setPosition(playerShape.getPosition().x - speed, playerShape.getPosition().y);
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

void Player::MovementShipsShape()
{
	shipsShape.setPosition(playerShape.getPosition());
	sf::Transform matrix = shipsShape.getTransform();
	std::list<Ship *>::iterator it = ships.begin();
	int i = 0;
	while (it != ships.end())
	{
		(*it)->posShip = matrix.transformPoint(shipsShape.getPoint(i));
		it++;
		i++;
	}
}

void Player::GetShip(Ship *ship)
{
	//int shipPositions = ships.size() > 3 ? ships.size() : 3;
	sf::Transform matrix = shipsShape.getTransform();
	shipsShape.setPointCount(shipsShape.getPointCount() + 1);
	ship->posShip = matrix.transformPoint(shipsShape.getPoint(shipsShape.getPointCount() - 1));
	ships.push_back(ship);
}

void Player::TakeDamage(int damages)
{
	lifeP -= damages;

	for (int i = 0; i < damages; i++)
	{
		delete ships.back();
		ships.pop_back();
	}
}
void Player::PlayerDeath()
{
	if (lifeP <= 0)
	{
		DestroyObject(this);
	}
}
void Player::DestroyBullet()
{
	std::list<Bullet*>::iterator ite = bullets.begin();
	while (ite != bullets.end())
	{
		if ((*ite)->shapeB.getPosition().y < 0 || (*ite)->shapeB.getPosition().x < 0 || (*ite)->shapeB.getPosition().y > 1500 || (*ite)->shapeB.getPosition().x > 2500)
		{
				DestroyObject(*ite);
			ite = bullets.erase(ite);
		}
		else
		{
			ite++;
		}
	}
}

sf::Vector2f Player::GetTraj(sf::RenderWindow* window, sf::Vector2f pos)
{
	sf::Vector2i mousePosInt = mouse.getPosition(*window);
	sf::Vector2f mousePos(mousePosInt);
	sf::Vector2f trajectoireBullet = (mousePos - pos);
	float distance = sqrt(powf(trajectoireBullet.x, 2) + powf(trajectoireBullet.y, 2));
	sf::Vector2f trajNormalized = trajectoireBullet / distance;
	return trajNormalized;
}