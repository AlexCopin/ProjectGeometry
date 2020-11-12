#pragma once
#include "Main.h"
class Enemy : Object
{
public:
	int lifeE = 0;
	int speedE = 0;
	//sf::Shape enemyShape;
	//TYPEBULLET enemyType;
	int posX = 0;
	int posY = 0;
	Enemy *CreateEnemy(int life, int speed, int posX, int posY);
};