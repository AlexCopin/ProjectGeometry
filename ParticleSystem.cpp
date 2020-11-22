#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int count, float duration, sf::Vector2f position, sf::Color color, sf::Vector2f size)
{
	this->count = count;
	this->duration = duration;
	for (int i = 0; i < count; i++)
	{
		sf::RectangleShape* point = new sf::RectangleShape;
		point->setPosition(position);
		point->setFillColor(color);
		point->setSize(size);
		points.push_back(point);
	}
}

void ParticleSystem::Update(sf::RenderWindow* window, float deltaTime)
{
	duration -= deltaTime;
		MoveParticles(deltaTime);
		DrawParticles(window);
		if(duration <= 0)
		{
			DestroyParticles();
			DestroyObject2(this);
		}
}

void ParticleSystem::MoveParticles(float deltaTime)
{
	
	std::list<sf::RectangleShape*>::iterator it = points.begin();
	while (it != points.end())
	{
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 500);
		float newSpeed = speed * deltaTime;
		(*it)->setPosition((*it)->getPosition() + VectorNewAngle(ConvertRadToDeg(angle), { 1, 1 }) * newSpeed);
		it++;
	}
}

void ParticleSystem::DrawParticles(sf::RenderWindow* window)
{
	std::list<sf::RectangleShape*>::iterator it = points.begin();
	while (it != points.end())
	{
		window->draw(**it);
		it++;
	}
}

void ParticleSystem::DestroyParticles()
{
	std::list<sf::RectangleShape*>::iterator it = points.begin();
	while (it != points.end())
	{
		delete (*it);
		it = points.erase(it);
	}
}