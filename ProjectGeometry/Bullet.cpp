#include "Bullet.h"
void Bullet::Start(sf::RenderWindow* window)
{
	typeB = TYPEBULLET::TRIANGLE;
	player = (Player*)FindObject("Player");
}
void Bullet::Update(sf::RenderWindow* window, float deltaTime)
{
	/*sf::Mouse mouse;
	Bullet* boule;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		 boule = Bullet::CreateBullet(2, typeB, player->posX, player->posY);
	}
	MoveBullet(0.5f, mouse, boule, window);*/
}


Bullet *Bullet::CreateBullet(int damage, TYPEBULLET typeShape, int posX, int posY)
{
	Bullet *bullet = new Bullet;
	std::size_t count = 0;
	if (typeShape == TYPEBULLET::STICK)
	{
		count = 2;
	}
	else if (typeShape == TYPEBULLET::TRIANGLE)
	{
		count = 3;
	}
	else if (typeShape == TYPEBULLET::SQUARE)
	{
		count = 4;
	}
	else if (typeShape == TYPEBULLET::PENTAGONE)
	{
		count = 5;
	}
	else if (typeShape == TYPEBULLET::HEXAGONE)
	{
		count = 6;
	}
	bullet->originPosX = posX;
	bullet->originPosY = posY;
	bullet->damageB = damage;
	bullet->typeB = typeShape;
	bullet->shapeB.setPointCount(count);
	bullet->shapeB.setPosition(posX, posY);
	return bullet;
}
void Bullet::MoveBullet(float speed, sf::Mouse mouse, Bullet* bullet, sf::RenderWindow *window)
{
	sf::Vector2i posMouse = mouse.getPosition(*window);
	sf::Vector2i originPosBullet(bullet->originPosX, bullet->originPosY);
	sf::Vector2i trajectoireBullet(posMouse - originPosBullet);
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	bullet->shapeB.setPosition(trajectoireBullet.x * (timeInSeconds * speed), trajectoireBullet.y * (timeInSeconds * speed));
	window->draw(bullet->shapeB);
	if (timeInSeconds > 3.0f) {
		DestroyObject(bullet);
	}
}
