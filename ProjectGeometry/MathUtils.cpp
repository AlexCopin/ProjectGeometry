#include "MathUtils.h"
const float IIM_PI = 3.14159265358979323846f;
float ConvertRadToDeg(float radian)
{
	return radian * 180.0f / IIM_PI;
}
float ConvertDegToRad(float degree)
{
	return degree * IIM_PI / 180.0f;
}
float GetMax(float a, float b)
{
	return a > b ? a : b;
}
float GetMin(float a, float b)
{
	return a < b ? a : b;
}
int GetMax(int a, int b)
{
	return a > b ? a : b;
}
int GetMin(int a, int b)
{
	return a < b ? a : b;
}
float Magnitude(sf::Vector2f vdirection, sf::Vector2f vdirection2)
{
	float magnitude;
	sf::Vector2f v3 = vdirection - vdirection2;
	magnitude = sqrt(v3.x * v3.x + v3.y * v3.y);
	return magnitude;
}
sf::Vector2f VectorNewAngle(float angle, sf::Vector2f direction)
{
	sf::Vector2f newVector;
	newVector.x = direction.x * cos(angle) - direction.y * sin(angle);
	newVector.y = direction.x * sin(angle) + direction.y * cos(angle);
	return newVector;
}
sf::Vector2f Normalized(sf::Vector2f vector)
{
	float distance = sqrt(powf(vector.x, 2) + powf(vector.y, 2));
	sf::Vector2f vectorNormalized = vector / distance;
	return vectorNormalized;
}