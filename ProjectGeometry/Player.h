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
	float speedP = 2.0f;
	sf::Mouse mouse;
	sf::CircleShape playerShape;
	sf::Vector2f posPlayer;
	//ALEXBULLET
	int damageP = 2;
	float speedBulletP = 30.0f;
	std::list<sf::Vector2f> trajectoriesBullets;
	float shootTimer = 0.5f;
	float shootTimerValue = 0.2f;
	static Player* player;
	void ShootBullet(sf::RenderWindow* window, float deltaTime);
	sf::CircleShape shipsShape;
	void MovePlayer(std::string direction);
	void RotatePlayer(sf::RenderWindow *window);
	float GetTime();
	void TakeDamage(int damages);
	void PlayerDeath();
	void DestroyBullet();
	void GetShip(Ship *ship);
	void ShipShootBullet(sf::RenderWindow* window, float deltaTime);
	void MovementShipsShape();
	Player(std::string id, int life, int posX, int posY);
	sf::Vector2f GetTraj(sf::RenderWindow* window, sf::Vector2f pos);
	void Update(sf::RenderWindow *window, float deltaTime);
};
