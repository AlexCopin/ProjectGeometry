#pragma once
#include "Main.h"
class Bullet : Object
{
public:
	enum class TYPEBULLET
	{
		STICK,
		TRIANGLE,
		SQUARE,
		PENTAGONE,
		HEXAGONE
	};
	int damageB = 0;
	float speedB = 0.0f;
	TYPEBULLET typeB = TYPEBULLET::STICK;
	sf::CircleShape shapeB;
	int originPosX = 0;
	int originPosY = 0;
	Bullet *CreateBullet(int damage, TYPEBULLET typeShape, int posX, int posY);
	void MoveBullet(int speed, sf::Mouse mouse, Bullet &bullet, sf::Window window);
};