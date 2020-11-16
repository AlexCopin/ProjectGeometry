#include "Main.h"
class Player;
class Enemy : Object
{
public:
	enum class Type
	{
		Triangle,
		Square,
		Octagon,
		Circle
	} type;
	sf::Vector2f position;
	uint16_t health;
	float speed;
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
	Enemy(std::string id, sf::Vector2f position, Type type);
	void Update(sf::RenderWindow *window, float deltaTime);
};