#include "Behaviour.h"

sf::Vector2f Seek::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation)
{
	sf::Vector2f steering{ 0.0f,0.0f };

	steering = t_playerPos - t_currentPos;
	steering = steering.normalized();

	t_rotation = atan2(steering.y, steering.x) * 180.0f / M_PI;

	return steering;
}

sf::Keyboard::Key Seek::getKey()
{
	return sf::Keyboard::Key::Num1;
}

sf::Vector2f ArriveSlow::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation)
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

	t_rotation = atan2(steering.y, steering.x) * 180.0f / M_PI;

	return steering;
}

sf::Keyboard::Key ArriveSlow::getKey()
{
	return sf::Keyboard::Key::Num2;
}

sf::Vector2f ArriveFast::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation)
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

	t_rotation = atan2(steering.y, steering.x) * 180.0f / M_PI;

	return steering;
}

sf::Keyboard::Key ArriveFast::getKey()
{
	return sf::Keyboard::Key::Num3;
}

sf::Vector2f Wander::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation)
{
	sf::Vector2f steering{ 0.0f,0.0f };
	
	//float wanderOffset = 10.0f;
	//float wanderRadius = 5.0f;
	//float wanderRate = 1.0f;
	//float wanderOrientation = 0.0f;
	//float maxAcc = 4.0f;

	//wanderOrientation += (rand() % 3 - 1) * wanderRate;
	//float targetOrientation = wanderOrientation + t_rotation;

	//// Get center of wander circle
	//sf::Vector2f targetCenter = t_currentPos + (sf::Vector2f(1.0f, t_rotation) * wanderOffset);
	//targetCenter += wanderRadius * sf::Vector2f(1.0f, sf::Angle(sf::degrees(targetOrientation)));

	//steering = targetCenter - t_currentPos;
	//t_rotation = targetOrientation;

	steering = t_playerPos - t_currentPos;
	steering = steering.normalized();
	t_rotation = t_rotation + (rand() % 3 - 1) * 3.0f;
	steering = sf::Vector2f(1.0f, sf::Angle(sf::degrees(t_rotation)));

	return steering;
}

sf::Keyboard::Key Wander::getKey()
{
	return sf::Keyboard::Key::Num4;
}