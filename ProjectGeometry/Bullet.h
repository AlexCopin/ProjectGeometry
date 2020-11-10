#pragma once

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
	TYPEBULLET typeB;
};


Bullet* CreateBullet(int damage, int speed, TYPEBULLET typeShape)
{

}