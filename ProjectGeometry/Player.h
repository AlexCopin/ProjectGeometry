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
	float Movx = 0;
	float Movy = 0;
	sf::Vector2f Movement = sf::Vector2f(0,0);
	float speedP = 400;
	float actualSpeed = 0;
	sf::Mouse mouse;
	sf::CircleShape playerShape;
	sf::Vector2f posPlayer;
	//ALEXBULLET
	int damageP = 2;
	std::list<sf::Vector2f> trajectoriesBullets;
	float shootTimer = 0.5f;
	float shootTimerValue = 0.2f;
	float shootTimerShip = 0.4f;
	float shootTimerShipValue = 0.1f;
	static Player* player;
	void ShootBullet(sf::RenderWindow* window, float deltaTime);
	sf::CircleShape shipsShape;
	float shipsShapeAngle = 0;
	void MovePlayer(float x, float y, float speed, float deltaTime);
	void RotatePlayer(sf::RenderWindow *window);
	float GetTime();
	void TakeDamage(int damages);
	void PlayerDeath();
	void DestroyBullet();
	void GetShip(Ship *ship);
	void ShipShootBullet(sf::RenderWindow* window, float deltaTime);
	void MovementShipsShape(float deltaTime);
	Player(std::string id, int life, int posX, int posY);
	sf::Vector2f GetTraj(sf::RenderWindow* window, sf::Vector2f pos);
	void Update(sf::RenderWindow *window, float deltaTime);
};
