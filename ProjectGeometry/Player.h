#pragma once
#include "Main.h"
#include "Ship.h"
#include "Bullet.h"
#include <list>
class Player : Object
{
public:
	enum class TYPEBULLET
	{
		TRIANGLE,
		SQUARE,
		PENTAGONE,
		HEXAGONE
	} typeB;
	TYPEBULLET typeWeapon = TYPEBULLET::TRIANGLE;
	int lifeP = 0;
	float speedP = 0.0f;
	sf::Mouse mouse;
	sf::CircleShape playerShape;
	sf::Vector2f posPlayer;
	//ALEXBULLET
	int damageP = 2;
	float speedBulletP = 10.0f;
	std::list<sf::Vector2f> trajectoriesBullets;
	float shootTimer = 0.5f;
	float shootTimerValue = 0.2f;
	static Player* player;

	sf::CircleShape shipsShape;
	void MovePlayer(std::string direction);
	void RotatePlayer(sf::RenderWindow *window);
	float GetTime();
	void TakeDamage(int damages);
	void PlayerDeath();
	void GetShip(Ship *ship);
	void MovementShipsShape();
	Player(std::string id, int life, float speed, int posX, int posY);

	void Update(sf::RenderWindow *window, float deltaTime);
};
