#include "Behaviour.h"

sf::Vector2f Seek::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos)
{
	sf::Vector2f steering{ 0.0f,0.0f };

	steering = t_playerPos - t_currentPos;
	steering = steering.normalized();

	return steering;
}

sf::Keyboard::Key Seek::getKey()
{
	return sf::Keyboard::Key::Num1;
}

sf::Vector2f ArriveSlow::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos)
{
	sf::Vector2f steering{ 0.0f,0.0f };
	float radius = 30.0f;
	float timeToTarget = 0.25f;
	float t_maxSpeed = 1.0f;
	
	steering = t_playerPos - t_currentPos;
	if (steering.length() < radius)
	{
		steering = sf::Vector2f{ 0.0f,0.0f };
		return steering;
	}
	else
	{
		steering = steering / timeToTarget;
		if (steering.length() > t_maxSpeed)
		{
			steering = steering.normalized() * t_maxSpeed;
		}
	}

	return steering;
}

sf::Keyboard::Key ArriveSlow::getKey()
{
	return sf::Keyboard::Key::Num2;
}

sf::Vector2f ArriveFast::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos)
{
	sf::Vector2f steering{ 0.0f,0.0f };
	float radius = 30.0f;
	float timeToTarget = 0.25f;
	float t_maxSpeed = 2.0f;

	steering = t_playerPos - t_currentPos;
	if (steering.length() < radius)
	{
		steering = sf::Vector2f{ 0.0f,0.0f };
		return steering;
	}
	else
	{
		steering = steering / timeToTarget;
		if (steering.length() > t_maxSpeed)
		{
			steering = steering.normalized() * t_maxSpeed;
		}
	}

	return steering;
}

sf::Keyboard::Key ArriveFast::getKey()
{
	return sf::Keyboard::Key::Num3;
}

sf::Vector2f Wander::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos)
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
