#include "Main.h"
class Map;
class Player;
class Enemy : Object
{
public:
	// Map
	Map *map;
	// Variables
	enum class Type
	{
		Triangle,
		Square,
		Circle,
		Octagon
	} type;
	sf::Vector2f position;
	uint16_t health;
	float speed;
	sf::Clock clock;
	// Appearance
	sf::CircleShape shape;
	sf::Color color;
	float radius;
	// Player
	Player *player;
	// Target
	sf::Vector2f target;
	bool isDirVert;
	float patrolTime = 2;
	float timer = patrolTime;
	float isOnTarget = 1;
	float amplitude = .5;
	Enemy(std::string id, sf::Vector2f position, Type type);
	void Update(sf::RenderWindow *window, float deltaTime);
};