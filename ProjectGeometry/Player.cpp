#include "Player.h"

Player* player = new Player;

void Player::Start(sf::RenderWindow* window)
{
	this->id = "Player";
	player = player->CreatePlayer(5, 0.2f, 50, 50);
}


void Player::Update(sf::RenderWindow *window, float deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// left key is pressed: move our character
		MovePlayer(*player, "left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// left key is pressed: move our character
		MovePlayer(*player, "right");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		// left key is pressed: move our character
		MovePlayer(*player, "up");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// left key is pressed: move our character
		MovePlayer(*player, "down");
	}
	player->posX = player->playerShape.getPosition().x;
	player->posY = player->playerShape.getPosition().y;
	window->draw(player->playerShape);
}







Player *Player::CreatePlayer(int life, float speed, int posX, int posY)
{
	Player *player = new Player();
	player->lifeP = life;
	player->speedP = speed;
	player->posX = posX;
	player->posY = posY;
	sf::Vector2f PosPlayer(posX, posY);
	player->playerShape.setPosition(PosPlayer);
	player->playerShape.setRadius(50.0f);
	player->playerShape.setFillColor(sf::Color::White);
	return player;
}
void Player::MovePlayer(Player& player, std::string direction)
{
	if (direction == "up")
	{
		player.playerShape.setPosition(player.playerShape.getPosition().x, player.playerShape.getPosition().y - player.speedP);
	}
	else if (direction == "right")
	{
		player.playerShape.setPosition(player.playerShape.getPosition().x + player.speedP , player.playerShape.getPosition().y);
	}
	else if (direction == "down")
	{
		player.playerShape.setPosition(player.playerShape.getPosition().x, player.playerShape.getPosition().y + player.speedP);
	}
	else if (direction == "left")
	{
		player.playerShape.setPosition(player.playerShape.getPosition().x - player.speedP, player.playerShape.getPosition().y);
	}
	return;
}
void Player::RotatePlayer(Player *player, sf::RenderWindow *window)
{
	sf::Vector2i cursor = sf::Mouse::getPosition((*window));
	//sf::Vector2f worldCursor = window.convertCoords(cursor.x, cursor.y);
	sf::Vector2f direction = sf::Vector2f(cursor.x, cursor.y) - player->playerShape.getPosition();
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
void Player::Fire(Player *player, bool canFire, int damages, int posX, int posY)
{
	if (canFire)
	{
		//CreateBullet(damages, player->weapon, posX, posY);
	}
}
void Player::TakeDamage(Player *player, int damages)
{
	player->lifeP -= damages;
}
void Player::PlayerDeath(Player *player)
{
	if (player->lifeP <= 0)
	{
		delete player;
	}
}