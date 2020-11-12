#include "Ship.h"


Ship::Ship(sf::Vector2f position, std::string id) {
	this->id = id;
	shipShape.setPointCount(3);
	shipShape.setFillColor(sf::Color::Cyan);
	shipShape.setRadius(10);
	shipShape.setPosition(position);
	shipShape.setOrigin(sf::Vector2f(10, 10));
}



void Ship::Update(sf::RenderWindow *window, float deltaTime)
{
	RotateShip(window);
	window->draw(shipShape);
}

void Ship::RotateShip(sf::RenderWindow *window)
{
	sf::Vector2i mousePositionInt = sf::Mouse::getPosition((*window));
	//std::cout << mousePositionInt.x << ", " << mousePositionInt.y << std::endl;
	sf::Vector2f mousePosition(mousePositionInt);
	sf::Vector2f shipToAim = mousePosition - shipShape.getPosition();
	float aimingAngle = atan2f(shipToAim.y, shipToAim.x);
	shipShape.setRotation(ConvertRadToDeg(aimingAngle + IIM_PI / 2.0f));
}
