#pragma once
#include "Main.h"
#include "Player.h"
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
	Player* player;
	int damageB = 0;
	float speedB = 0.0f;
	TYPEBULLET typeB = TYPEBULLET::STICK;
	sf::CircleShape shapeB;
	int originPosX = 0;
	int originPosY = 0;
	Bullet *CreateBullet(int damage, TYPEBULLET typeShape, int posX, int posY);
	void MoveBullet(float speed, sf::Mouse mouse, Bullet* bullet, sf::RenderWindow *window);
	void Start(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float deltaTime);
};