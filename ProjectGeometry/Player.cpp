#include "Player.h"

Player *player = new Player;

void Player::Start(sf::RenderWindow *window)
{
	this->id = "Player";
	player = player->CreatePlayer(5, 0.2f, 50, 50);
	typeWeapon = TYPEBULLET::TRIANGLE;
}


void Player::OnEvent(sf::RenderWindow* window, sf::Event event, float deltaTime) 
{
	sf::Mouse mouse;
	sf::Vector2i mousePosInt = mouse.getPosition(*window);
	sf::Vector2f mousePos( mousePosInt);
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (nextBulletTime <= 0)
		{
			Bullet* bullet = new Bullet(2, mousePos);
			LOG("Start fire");
		}else
		{
			nextBulletTime -= deltaTime;
			nextBulletTime = cadenceFire;
			LOG("Stop fire");
		}
	}
}

void Player::Update(sf::RenderWindow *window, float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// left key is pressed: move our character
		MovePlayer("left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// left key is pressed: move our character
		MovePlayer("right");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		// left key is pressed: move our character
		MovePlayer("up");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// left key is pressed: move our character
		MovePlayer("down");
	}
	posPlayer = playerShape.getPosition();
	window->draw(playerShape);
}

Player *Player::CreatePlayer(int life, float speed, int posX, int posY)
{
	lifeP = life;
	speedP = speed;
	posX = posX;
	posY = posY;
	posPlayer = sf::Vector2f(posX, posY);
	//std::size_t count = 5;
	//playerShape.setPointCount(count);
	playerShape.setPosition(posPlayer);
	playerShape.setRadius(50.0f);
	playerShape.setFillColor(sf::Color::White);
	return player;
}
void Player::MovePlayer(std::string direction)
{
	if (direction == "up")
	{
		playerShape.setPosition(playerShape.getPosition().x, playerShape.getPosition().y - speedP);
	}
	else if (direction == "right")
	{
		playerShape.setPosition(playerShape.getPosition().x + speedP, playerShape.getPosition().y);
	}
	else if (direction == "down")
	{
		playerShape.setPosition(playerShape.getPosition().x, playerShape.getPosition().y + speedP);
	}
	else if (direction == "left")
	{
		playerShape.setPosition(playerShape.getPosition().x - speedP, playerShape.getPosition().y);
	}
	return;
}
void Player::RotatePlayer(sf::RenderWindow *window)
{
	sf::Vector2i cursor = sf::Mouse::getPosition((*window));
	//sf::Vector2f worldCursor = window.convertCoords(cursor.x, cursor.y);
	sf::Vector2f direction = sf::Vector2f(cursor.x, cursor.y) - playerShape.getPosition();
	// player->playerShape.setRotation(std::atan2(direction.y, direction.x));
}
float Player::GetTime()
{
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	return timeInSeconds;
}


void Player::StartFire()
{
	isFiring = true;
	nextBulletTime = 0.0f;
}
void Player::StopFire()
{
	isFiring = false;
	nextBulletTime = cadenceFire;
	LOG("Stop fire");
}
void Player::Fire(bool canFire, int damages, int posX, int posY)
{
	
}
void Player::TakeDamage(int damages)
{
	lifeP -= damages;
}
void Player::PlayerDeath()
{
	if (lifeP <= 0)
	{
		DestroyObject(this);
	}
}