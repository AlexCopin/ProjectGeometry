#include "Main.h"
class Player;
class Enemy : Object
{
public:
	enum Type
	{
		Triangle,
		Square,
		Octagon,
		Circle
	} type;
	sf::CircleShape shape;
	sf::Vector2f position;
	uint16_t health, speed;
	Player *player;
	Enemy(std::string id, sf::Vector2f position, Type type);
	void Update(sf::RenderWindow *window, float deltaTime);
};