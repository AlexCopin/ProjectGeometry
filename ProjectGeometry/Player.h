#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "littleShip.h"

struct Ship;

struct Player
{
	int lifeP = 0;
	int speedP = 0;
	sf::CircleShape playerShape;
	Ship **playerShips;

	int posX = 0;
	int posY = 0;
};

Player* CreatePlayer(int life, int speed, int posX, int posY);

void MovePlayer(Player* player, bool up, bool right, bool down, bool left);
float GetTime();
bool canFire(float& time, float cadence);
void Fire(Player* player, bool canFire, int damages, int posX, int posY);
void TakeDamage(Player* player, int damages);
void PlayerDeath(Player* player);

