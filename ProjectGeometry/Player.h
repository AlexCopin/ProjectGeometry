#pragma once
#include "Main.h"
#include "Ship.h"
#include "Bullet.h"
class Player : Object
{
public:
	int lifeP = 0;
	float speedP = 0.0f;
	bool isFiring = false;
	float nextBulletTime = 0.0f;
	float cadenceFire = 1.0f;
	sf::CircleShape playerShape;
	Ship **playerShips;
	int posX = 0;
	int posY = 0;
	Player *CreatePlayer(int life, float speed, int posX, int posY);
	void MovePlayer(std::string direction);
	void RotatePlayer(sf::RenderWindow *window);
	float GetTime();
	//bool canFire(float &time, float cadence);
	Bullet* CreateBullet(int damage, TYPEBULLET typeShape, int posX, int posY);
	void StartFire();
	void StopFire();
	void Fire(bool canFire, int damages, int posX, int posY);
	void TakeDamage(int damages);
	void PlayerDeath();
	void Start(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, float deltaTime);
};