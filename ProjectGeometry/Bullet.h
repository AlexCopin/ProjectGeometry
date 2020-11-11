#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
enum class TYPEBULLET
{
	STICK,
	TRIANGLE,
	SQUARE,
	PENTAGONE,
	HEXAGONE
};
struct Bullet
{
	int damageB = 0;
	float speedB = 0.0f;
	TYPEBULLET typeB = TYPEBULLET::STICK;
	sf::CircleShape shapeB;
	int originPosX = 0;
	int originPosY = 0;
};


Bullet* CreateBullet(int damage, TYPEBULLET typeShape, int posX, int posY);

void MoveBullet(int speed, int posMouseX, int posMouseY, sf::Window window);