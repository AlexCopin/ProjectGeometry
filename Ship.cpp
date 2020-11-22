#include "Ship.h"
#include "Player.h"
Ship::~Ship()
{
	LOG("destroy Ship");
}
Ship::Ship(sf::Vector2f position, std::string id)
{
	// this->id = id;
	shipShape.setPointCount(3);
	shipShape.setFillColor(sf::Color::Cyan);
	shipShape.setRadius(10);
	shipShape.setScale(0.7f, 1.0f);
	shipShape.setPosition(position);
	posShip = position;
	shipShape.setOrigin(sf::Vector2f(10, 10));
	GetPlayer();
}
void Ship::Update(sf::RenderWindow *window, float deltaTime)
{
	GetDistanceWithPlayer();
	RotateShip(window);
	window->draw(shipShape);
	shipShape.setPosition(posShip);
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
void Ship::GetPlayer()
{
	player = (Player *)FindObject("Player");
}
void Ship::GetDistanceWithPlayer()
{
	if (!isWithPlayer)
	{
		sf::Vector2f shipToPlayer = player->posPlayer - shipShape.getPosition();
		float distance = sqrt(powf(shipToPlayer.x, 2) + powf(shipToPlayer.y, 2));
		if (distance < player->playerShape.getRadius() + (shipShape.getRadius()))
		{
			player->GetShip(this);
			isWithPlayer = true;
		}
		else
		{
			return;
		}
	}
}