#include "Enemy.h"

Enemy* CreateEnemy(int life, int speed, int posX, int posY) {
	Enemy* enemy = new Enemy();
	enemy->lifeE = life;
	enemy->speedE = speed;
	enemy->posX = posX;
	enemy->posY = posY;
	sf::Vector2f PosEnemy(posX, posY);
	//enemy->playerShape.setPosition(PosPlayer);
	//enemy->playerShape.setRadius(2.0f);
	//enemy->playerShape.setFillColor(sf::Color::White);

	return enemy;
}
