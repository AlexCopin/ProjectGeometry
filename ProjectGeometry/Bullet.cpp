#include "Bullet.h"
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
void Bullet::MoveBullet(int speed, sf::Mouse mouse, Bullet &bullet, sf::Window window)
{
	sf::Vector2i posMouse = mouse.getPosition(window);
	sf::Vector2i originPosBullet(bullet.originPosX, bullet.originPosY);
	sf::Vector2i trajectoireBullet(posMouse - originPosBullet);
	float timeInSeconds = clock() / (float)CLOCKS_PER_SEC;
	bullet.shapeB.setPosition(trajectoireBullet.x * (timeInSeconds * speed), trajectoireBullet.y * (timeInSeconds * speed));
}