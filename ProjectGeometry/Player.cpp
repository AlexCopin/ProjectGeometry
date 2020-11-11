#include "Player.h"
Player *Player::CreatePlayer(int life, int speed, int posX, int posY)
{
	Player *player = new Player();
	player->lifeP = life;
	player->speedP = speed;
	player->posX = posX;
	player->posY = posY;
	sf::Vector2f PosPlayer(posX, posY);
	player->playerShape.setPosition(PosPlayer);
	player->playerShape.setRadius(2.0f);
	player->playerShape.setFillColor(sf::Color::White);
	return player;
}
void Player::MovePlayer(Player *player, bool up, bool right, bool down, bool left)
{
	if (up)
	{
		player->posY++;
	}
	else if (right)
	{
		player->posX++;
	}
	else if (down)
	{
		player->posY--;
	}
	else if (left)
	{
		player->posX--;
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