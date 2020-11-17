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

	playerShape.setPosition(posPlayer);
	playerShape.setRadius(50.0f);
	playerShape.setFillColor(sf::Color::White);
	playerShape.setOrigin(50, 50);
	playerShape.setPointCount(10);

	shipsShape.setPosition(playerShape.getPosition());
	shipsShape.setRadius(70.0f);
	shipsShape.setPointCount(0);
	shipsShape.setFillColor(sf::Color::Transparent);
	shipsShape.setOutlineColor(sf::Color::Red);
	shipsShape.setOrigin(sf::Vector2f(70, 70));
	shipsShape.setOutlineThickness(3);
	typeB = TYPEBULLET::TRIANGLE;
	player = this;
}


void Player::Update(sf::RenderWindow *window, float deltaTime)
{
	bool isOneKeyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// left key is pressed: move our character
		MovePlayer(-1,0, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// left key is pressed: move our character
		MovePlayer(1,0, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		// left key is pressed: move our character
		MovePlayer(0,-1, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// left key is pressed: move our character
		MovePlayer(0,1, speedP, deltaTime);
		isOneKeyPressed = true;
	}
	
	if (!isOneKeyPressed) {
		float magnitude = sqrt(powf(Movement.x, 2) + powf(Movement.y, 2)) ;
		if (magnitude > 0) {

			float magnitude2 = magnitude - 600 * deltaTime;
			if (magnitude2 < 0) {
				magnitude2 = 0;
			}
			
			Movement = Movement / magnitude * magnitude2;
			
		}
		
	}
	playerShape.setPosition(playerShape.getPosition() + Movement * deltaTime);

	DestroyBullet();
	posPlayer = playerShape.getPosition();
	MovementShipsShape(deltaTime);
	//ChangeWeapon();
	window->draw(playerShape);
	window->draw(shipsShape);
	/*std::list<Ship*>::iterator it = ships.begin();
	while (it != ships.end()) {
		window->draw((*it)->shipShape);
	}*/
	
}

void Player::OnEvent(sf::RenderWindow* window, sf::Event event, float deltaTime)
{

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
	{
		ChangeWeapon();
	}
}

void Player::ShootBullet(sf::RenderWindow* window, float deltaTime)
{
	//BULLET ALEX
	sf::Vector2f playerCenter = sf::Vector2f(posPlayer.x + playerShape.getRadius() / 4 , posPlayer.y + playerShape.getRadius() /4);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (shootTimer >= shootTimerValue) //Shoot
		{
			
			if(typeB == TYPEBULLET::SQUARE)
			{

				Bullet* bullet = new Bullet(damageP, GetTraj(window, playerCenter)); 
				bullet->shapeB.setPosition(playerCenter);
				Bullet* bullet2 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(20),GetTraj(window, playerCenter)));
				bullet2->shapeB.setPosition(playerCenter);
				Bullet* bullet3 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(-20), GetTraj(window, playerCenter)));
				bullet3->shapeB.setPosition(playerCenter); 
				Bullet* bullet4 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(160), GetTraj(window, playerCenter)));
				bullet4->shapeB.setPosition(playerCenter);
				Bullet* bullet5 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(-160), GetTraj(window, playerCenter)));
				bullet5->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				bullets.push_back(bullet2);
				bullets.push_back(bullet3);
				bullets.push_back(bullet4);
				bullets.push_back(bullet5);
				shootTimer = 0;
			}else if(typeB == TYPEBULLET::HEXAGONE)
			{
				float angle = 1 + (rand() % 360);
				Bullet* bullet = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle), GetTraj(window, playerCenter)));
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				float angle2 = 1 + (rand() % 360);
				Bullet* bullet2 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle2), GetTraj(window, playerCenter)));
				bullet2->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet2);
				/*float angle3 = 1 + (rand() % 360);
				Bullet* bullet3 = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle3), GetTraj(window, playerCenter)));
				bullet3->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet3);*/
				shootTimer = 0;
			}else if(typeB == TYPEBULLET::BONUS)
			{
				float angle = 1 + (rand() % 360);
				Bullet* bullet = new Bullet(damageP, VectorNewAngle(ConvertRadToDeg(angle), GetTraj(window, playerCenter)));
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
			}
			else
			{
				Bullet* bullet = new Bullet(damageP, GetTraj(window, playerCenter)); 
				bullet->shapeB.setPosition(playerCenter);
				bullets.push_back(bullet);
				shootTimer = 0;
			}
			
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

	sf::Vector2f playerCenter = sf::Vector2f(posPlayer.x + playerShape.getRadius() / 2, posPlayer.y + playerShape.getRadius() / 2);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (shootTimerShip >= shootTimerShipValue) //Shoot
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
			shootTimerShip = 0;
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
	sf::Vector2f direction{ x,y };
	Movement += direction * (float)1000 * deltaTime;

	float magnitude = sqrt(powf(Movement.x, 2) + powf(Movement.y, 2));
	if (magnitude > speed) {
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
		if (distance > 0.1f) {
			direction2 = direction2 / distance;
			(*it)->posShip = (*it)->posShip + direction2 * (float)(i+2) *distance * deltaTime;
		}
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
	return  Normalized(trajectoireBullet);
}



void Player::ChangeWeapon()
{
	LOG("Change weapon");
	int newType = (int)typeB + 1;
	if(newType == (int)TYPEBULLET::SIZE)
	{
		newType = 0;
	}
	typeB = (TYPEBULLET)newType;
}