#include "Ship.h"
#include "MathUtils.h"
Ship *Ship::CreateShip(float x, float y, std::string id)
{
	Ship *ship = new Ship;
	ship -> id = id;
	shipShape.setPointCount(count);
	ship->posX = x;
	ship->posY = y;

	return ship;
}

void Ship::Start(sf::RenderWindow* window){

}

void Ship::Update(sf::RenderWindow* window, float deltaTime) {

	RotateShip(window);
}

void Ship::RotateShip(sf::RenderWindow* window) {
	sf::Vector2i mousePositionInt = sf::Mouse::getPosition((*window));
	//std::cout << mousePositionInt.x << ", " << mousePositionInt.y << std::endl;
	sf::Vector2f mousePosition(mousePositionInt);
	sf::Vector2f shipToAim = mousePosition - shipShape.getPosition();
	float aimingAngle = atan2f(shipToAim.y, shipToAim.x);
	shipShape.setRotation(ConvertRadToDeg(aimingAngle + IIM_PI / 2.0f));
}