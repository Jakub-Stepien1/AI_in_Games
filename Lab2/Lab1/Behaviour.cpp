#include "Behaviour.h"

sf::Vector2f Wander::getSteering()
{
	sf::Vector2f steering{ 0.0f,0.0f };
	float wanderOffset = 50.0f;
	float wanderRadius = 20.0f;
	float wanderRate = 2.0f;
	float wanderOrientation = 0.0f;
	float maxAcc = 4.0f;

	wanderOrientation += (rand() % 3 - 1) * wanderRate;


	return steering;
}
