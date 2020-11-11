#include"Player.h"

Player* CreatePlayer(int life, int speed, int posX, int posY) {
	Player* player = new Player();
	player->lifeP = life;
	player->speedP = speed;
	player->posX = posX;
	player->posY = posY;
	return player;
}

void MovePlayer(Player* player, bool up, bool right, bool down, bool left) {

	if (up) {
		player->posY++;
	}
	else if (right) {
		player->posX++;
	}
	else if (down) {
		player->posY--;
	}
	else if (left) {
		player->posX--;
	}
	return;

}