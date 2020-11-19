#pragma once
#include "Main.h"
#include "Ship.h"
#include "Bullet.h"
#include <list>
#include "SFML/Audio.hpp"
class Player : Object
{
public:
	enum class TYPEBULLET
	{
		BASE,
		SHOTGUN,
		MITRAILLETTE,
		CRAZY,
		BONUS,
		SIZE
	} typeB;
	int lifeP = 1;
	// Julien: Score
	int score;
	float Movx = 0;
	float Movy = 0;
	sf::Vector2f Movement = sf::Vector2f(0, 0);
	float speedP = 400;
	float actualSpeed = 0;
	sf::Mouse mouse;
	bool isMouseButtonDown = false;
	float bonusDuration = 0.0f;
	float bonusDurationValue = 1.5f;
	sf::CircleShape playerShape;
	sf::Vector2f posPlayer;
	//ALEXBULLET
	float damageP = 100;
	float damageShip = 0.5f;
	std::list<sf::Vector2f> trajectoriesBullets;
	float shootTimer = 0.5f;
	float shootTimerValue = 0.2f;
	float shootTimerShip = 0.4f;
	float shootTimerShipValue = 0.1f;
	static Player *player;

	sf::SoundBuffer buffer_gun;
	sf::SoundBuffer buffer_rifle1;
	sf::SoundBuffer buffer_rifle2;
	sf::SoundBuffer buffer_rifle3;
	sf::SoundBuffer buffer_rifle4;
	sf::SoundBuffer buffer_rifleEnd;
	sf::SoundBuffer buffer_shotgun;
	sf::SoundBuffer buffer_other;

	// on charge quelque chose dans le buffer...

	sf::Sound sound;

	void ShootBullet(sf::RenderWindow *window, float deltaTime);
	sf::CircleShape shipsShape;
	float shipsShapeAngle = 0;
	void MovePlayer(float x, float y, float speed, float deltaTime);
	void RotatePlayer(sf::RenderWindow *window);
	float GetTime();
	void TakeDamage(int damages);
	void PlayerDeath();
	void DestroyBullet();
	void ChangeWeapon();
	void GetShip(Ship *ship);
	void ShipShootBullet(sf::RenderWindow *window, float deltaTime);
	void MovementShipsShape(float deltaTime);
	Player(std::string id, int life, int posX, int posY);
	sf::Vector2f GetTraj(sf::RenderWindow *window, sf::Vector2f pos);
	void Update(sf::RenderWindow *window, float deltaTime);
	void OnEvent(sf::RenderWindow *window, sf::Event event, float deltaTime);
	void GameOver(sf::RenderWindow *window);
};
