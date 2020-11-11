#include"Player.h"

Player* CreatePlayer(int life, int speed, int posX, int posY) {
	Player* player = new Player();
	player->lifeP = life;
	player->speedP = speed;
	player->posX = posX;
	player->posY = posY;
	sf::Vector2f PosPlayer(posX, posY);
	player->playerShape.setPosition(PosPlayer);
	player->playerShape.setRadius(2.0f);
	player->playerShape.setFillColor(sf::Color::White);

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

float GetTime() {
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	return timeInSeconds;
}

//Preciser float time = GetTime() en debut de jeu 
bool canFire(float& time, float cadence) {
	if (GetTime() < time + cadence) {
		return false;
	}
	else {
		time = GetTime();
		return true;
	}
}

void Fire(Player* player, bool canFire, int damages, int posX, int posY) {
	if (canFire) {
		//CreateBullet(damages, player->weapon, posX, posY); 
	}

}

void TakeDamage(Player* player, int damages) {
	player->lifeP -= damages;
}


void PlayerDeath(Player* player) {
	if (player->lifeP <= 0) {
		delete player;
	}
}
