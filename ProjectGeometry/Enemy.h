#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>

enum class TYPEBULLET
{
	STICK,
	TRIANGLE,
	SQUARE,
	PENTAGONE,
	HEXAGONE
};

struct Enemy
{
	int lifeE = 0;
	int speedE = 0;
	//sf::Shape enemyShape;
	TYPEBULLET enemyType;

	int posX = 0;
	int posY = 0;
};

Enemy* CreateEnemy(int life, int speed, int posX, int posY);