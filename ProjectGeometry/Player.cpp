#include "Player.h"

Player *player = new Player;

void Player::Start(sf::RenderWindow *window)
{
	this->id = "Player";
	player = player->CreatePlayer(5, 0.2f, 50, 50);
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
	posX = playerShape.getPosition().x;
	posY = playerShape.getPosition().y;
	window->draw(playerShape);
}

Player *Player::CreatePlayer(int life, float speed, int posX, int posY)
{
	lifeP = life;
	speedP = speed;
	posX = posX;
	posY = posY;
	sf::Vector2f PosPlayer(posX, posY);
	playerShape.setPosition(PosPlayer);
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
//Preciser float time = GetTime() en debut de jeu
bool Player::canFire(float &time, float cadence)
{
	if (GetTime() < time + cadence)
	{
		return false;
	}
	else
	{
		time = GetTime();
		return true;
	}
}
void Player::Fire(bool canFire, int damages, int posX, int posY)
{
	if (canFire)
	{
		//CreateBullet(damages, weapon, posX, posY);
	}
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