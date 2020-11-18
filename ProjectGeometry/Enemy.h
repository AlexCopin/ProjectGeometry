#include "Main.h"
class Map;
class Player;
class Enemy : Object
{
public:
	// Map
	Map *map;
	// Player
	Player *player;
	// Variables
	enum class Type
	{
		Triangle,
		Square,
		Circle,
		Octagon
	} type;
	sf::Vector2f position;
	uint16_t health, damage;
	float speed, speedX, speedY;
	sf::Clock clock;
	// Appearance
	sf::CircleShape shape;
	sf::Color color;
	float radius;
	// Target
	sf::Vector2f target;
	bool isDirVert;
	float patrolTime;
	float timer = patrolTime;
	float isOnTarget = 1;
	float amplitude = 2;
	// Square
	bool isRot;
	// Bullet
	float cadence;
	float timerBul = cadence;
	void ShootBul(float deltaTime, sf::Vector2f dir, float angle);
	Enemy(std::string id, sf::Vector2f position, Type type);
	void Update(sf::RenderWindow *window, float deltaTime);
};