#include "Background.h"
#include <list>
#include "MathUtils.h"
// ENTITY
const float INITIAL_SPEED = 500.0f; // Initial speed of entity. Value in pixel per second.
const float FRICTION = -0.5f;		// Friction that will reduce speed during lifetime.
const float ROTATION_SPEED = 5.0f;	// Entity will spin on self. Value in degree per second.
const float LIFE_TIME = 5.0f;		// Entity will live during this duration. After what, it will be ready to be destroyed.
const float FADE_DURATION = 1.0f;	// Duration at end of entity life where entity will "fade" (color alpha from 0 to 1)
const int NUMBER_STARS = 750;
const float ENTITY_SPAWN_PERIOD = 1.0f;
//TEST ENTITIES
float entitySpawnTimer = 0.0f;
std::list<Entity *> entities;
std::list<Star *> stars;
Background::Background(std::string id, sf::RenderWindow *window)
{
	// this->id = id;
}
void Background::Update(sf::RenderWindow *window, float deltaTime)
{
	std::list<Star *>::iterator starsIt = stars.begin();
	while (starsIt != stars.end())
	{
		(*starsIt)->DrawStars(window);
		starsIt++;
	}
	std::list<Entity *>::iterator entityIte = entities.begin();
	while (entityIte != entities.end())
	{
		DrawEntity(*entityIte, *window);
		entityIte++;
	}
}
//ENTITY BACKGROUND
Entity *Background::CreateEntity(float x, float y, float dirAngle)
{
	Entity *pEntity = new Entity;
	pEntity->shape.setSize({SIZE, SIZE});
	pEntity->shape.setOrigin(SIZE / 2.0f, SIZE / 2.0f);
	pEntity->shape.setFillColor(sf::Color::White);
	pEntity->shape.setPosition(x, y);
	pEntity->timeToLive = LIFE_TIME;
	pEntity->speed = INITIAL_SPEED;
	pEntity->direction = {cos(ConvertDegToRad(dirAngle)), sin(ConvertDegToRad(dirAngle))};
	return pEntity;
}
Star::Star(float x, float y, sf::Color color, float size)
{
	star.setPosition({x, y});
	star.setSize({size, size});
	star.setFillColor(color);
}
void Star::DrawStars(sf::RenderWindow *window)
{
	window->draw(star);
}
void Background::UpdateB(Entity *pEntity, float deltaTime)
{
	pEntity->speed -= pEntity->speed * FRICTION * deltaTime;
	pEntity->shape.move(pEntity->direction * pEntity->speed * deltaTime);
	// Update entity lifetime
	pEntity->timeToLive -= deltaTime;
	// Update visibility
	if (pEntity->timeToLive < LIFE_TIME)
	{
		sf::Color color = pEntity->shape.getFillColor();
		if (pEntity->timeToLive < 0)
		{
			color.a = 0.0f;
		}
		else
		{
			color.a = pEntity->timeToLive * 255 / LIFE_TIME;
		}
		pEntity->shape.setFillColor(color);
	}
}
// Draw entity on screen every frame
void Background::DrawEntity(Entity *pEntity, sf::RenderWindow &window)
{
	window.draw(pEntity->shape);
}
// Check if entity is alive (timeToLive > 0)
bool Background::IsAlive(Entity *pEntity)
{
	return pEntity->timeToLive > 0;
}
// Deallocate everything that entity possess
void Background::Destroy(Entity *pEntity)
{
	delete pEntity;
}
void Background::CreateStars(sf::RenderWindow &window)
{
	//STARS
	std::list<Star *>::iterator starsIt = stars.begin();
	for (int i = 0; i < NUMBER_STARS; i++)
	{
		float randomX = rand() * window.getSize().x / (float)RAND_MAX;
		float randomY = rand() * window.getSize().y / (float)RAND_MAX;
		float colorAlpha = 1 + (rand() % 256);
		sf::Color color(255, 255, 255, colorAlpha);
		float sizeStar = 1 + (rand() % 3);
		Star *star = new Star(randomX, randomY, color, sizeStar);
		stars.push_back(star);
	}
}
void Background::SpawnEntities(sf::RenderWindow &window, float deltaTime)
{
	entitySpawnTimer += deltaTime;
	if (entitySpawnTimer > ENTITY_SPAWN_PERIOD)
	{
		entitySpawnTimer = 0.0f;
		float randomX = rand() * window.getSize().x / (float)RAND_MAX;
		float randomY = rand() * window.getSize().y / (float)RAND_MAX;
		float randomAngle = rand() * 360.0f / (float)RAND_MAX;
		Entity *pNewEntity = CreateEntity(randomX, randomY, randomAngle);
		entities.push_back(pNewEntity);
	}
}
void Background::DestroyEntities()
{
	std::list<Entity *>::iterator entityIt = entities.begin();
	while (entityIt != entities.end())
	{
		Destroy(*entityIt);
		entityIt++;
	}
}
void Background::EndEntities(float deltaTime)
{
	std::list<Entity *>::iterator entityIt = entities.begin();
	while (entityIt != entities.end())
	{
		UpdateB(*entityIt, deltaTime);
		if (!IsAlive(*entityIt))
		{
			Destroy(*entityIt);
			entityIt = entities.erase(entityIt);
		}
		else
		{
			entityIt++;
		}
	}
}