#pragma once
#include "Main.h"
struct Entity
{
	sf::RectangleShape shape;
	float timeToLive;
	sf::Vector2f direction;
	float speed;
};
struct Star
{
	sf::RectangleShape star;
	Star(float x, float y, sf::Color color, float size);
	void DrawStars(sf::RenderWindow *window);
};
class Background :public Object
{
public:
	//ENTITY
	float SIZE = 5.0f;
	Entity *CreateEntity(float x, float y, float dirAngle);
	void UpdateB(Entity *pEntity, float deltaTime);
	void DrawEntity(Entity *pEntity, sf::RenderWindow &window);
	bool IsAlive(Entity *pEntity);
	void Destroy(Entity *pEntity);
	//STARS
	void CreateStars(sf::RenderWindow &window);
	void Update(sf::RenderWindow *window, float deltaTime);
	void SpawnEntities(sf::RenderWindow &window, float deltaTime);
	void DestroyEntities();
	void EndEntities(float deltaTime);
	Background(std::string, sf::RenderWindow *window);
};