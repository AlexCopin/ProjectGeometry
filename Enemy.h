#include "Main.h"
#include "Bonus.h"
class Map;
class Player;
class Enemy :public Object
{
public:
	int loot;
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
	int health, damage, score;
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
	short bulCount;
	float speedSquare = 500.0f;
	float speedOctagon = 500.0f;
	float speedCircle = 500.0f;

	sf::SoundBuffer buffer_death;
	sf::Sound* sound = getSoundEnemy();

	void ShootBul(float deltaTime, sf::Vector2f dir, float angle);
	Enemy(std::string id, sf::Vector2f position, Type type);
	~Enemy();
	void Update(sf::RenderWindow *window, float deltaTime);
};