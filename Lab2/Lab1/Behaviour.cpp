#include "Behaviour.h"

SteeringOutput Seek::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity)
{
	SteeringOutput steering;

	float maxAcc = 8.0f;

	sf::Vector2f direction = t_playerPos - t_currentPos;
	steering.linear = direction;
	steering.linear = steering.linear.normalized() * maxAcc;

	steering.angular = 0;
	t_rotation = atan2(direction.y, direction.x) * 180.0f / M_PI;

	return steering;
}

sf::Keyboard::Key Seek::getKey()
{
	return sf::Keyboard::Key::Num1;
}

SteeringOutput ArriveSlow::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity)
{
	SteeringOutput steering;
	
	float arrivalRadius = 40.0f;
	float slowRadius = 200.0f;
	float timeToTarget = 0.25f;
	float maxSpeed = 2.0f;
	float maxAcceleration = 8.0f;
	float targetSpeed = 0;

	sf::Vector2f direction = t_playerPos - t_currentPos;
	float distance = direction.length();

	//Set Speed
	if (distance < arrivalRadius)
	{
		targetSpeed = 0;
	}
	else if (distance > slowRadius)
	{
		targetSpeed = maxSpeed;
	}
	else
	{
		targetSpeed = maxSpeed * (distance / slowRadius);
	}
	sf::Vector2f targetVelocity = direction;
	targetVelocity = targetVelocity.normalized() * targetSpeed;

	steering.linear = targetVelocity - t_velocity;
	steering.linear = steering.linear / timeToTarget;

	if (steering.linear.length() > maxAcceleration)
	{
		steering.linear = steering.linear.normalized() * maxAcceleration;
	}
	steering.angular = 0;

	t_rotation = atan2(direction.y, direction.x) * 180.0f / M_PI;

	return steering;
}

sf::Keyboard::Key ArriveSlow::getKey()
{
	return sf::Keyboard::Key::Num2;
}

SteeringOutput ArriveFast::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity)
{
	SteeringOutput steering;

	float arrivalRadius = 40.0f;
	float slowRadius = 200.0f;
	float timeToTarget = 0.25f;
	float maxSpeed = 6.0f;
	float maxAcceleration = 8.0f;
	float targetSpeed = 0;

	sf::Vector2f direction = t_playerPos - t_currentPos;
	float distance = direction.length();

	//Set Speed
	if (distance < arrivalRadius)
	{
		targetSpeed = 0;
	}
	else if (distance > slowRadius)
	{
		targetSpeed = maxSpeed;
	}
	else
	{
		targetSpeed = maxSpeed * (distance / slowRadius);
	}
	sf::Vector2f targetVelocity = direction;
	targetVelocity = targetVelocity.normalized() * targetSpeed;

	steering.linear = targetVelocity - t_velocity;
	steering.linear = steering.linear / timeToTarget;

	if (steering.linear.length() > maxAcceleration)
	{
		steering.linear = steering.linear.normalized() * maxAcceleration;
	}
	steering.angular = 0;

	t_rotation = atan2(direction.y, direction.x) * 180.0f / M_PI;

	return steering;
}

sf::Keyboard::Key ArriveFast::getKey()
{
	return sf::Keyboard::Key::Num3;
}

SteeringOutput Wander::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity)
{
	SteeringOutput steering;
	
	float wanderOffset = 50.0f;
	float wanderRadius = 10.0f;
	float wanderRate = 1.0f;
	float wanderOrientation = 0.0f;
	float maxAcc = 8.0f;

	wanderOrientation += (rand() % 100 + 1) / 100 - 0.5f;
	float targetOrientation = t_rotation + wanderOrientation;
	//Get centre of circle

	// Kinematic
	//steering.linear = t_playerPos - t_currentPos;
	//steering.linear = steering.linear.normalized();
	//t_rotation = t_rotation + (rand() % 3 - 1) * 2.0f;
	//steering.linear = sf::Vector2f(1.0f, sf::Angle(sf::degrees(t_rotation)));

	return steering;
}

sf::Keyboard::Key Wander::getKey()
{
	return sf::Keyboard::Key::Num4;
}

SteeringOutput Pursue::getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity)
{
	SteeringOutput steering;

	steering.linear = t_playerPos - t_currentPos;
	float distance = steering.linear.length();
	float maxTimePrediction = 10.0f;
	float timePrediction = 0;
	float speed = t_velocity.length();

	if (speed <= distance/maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else
	{
		timePrediction = distance / speed;
	}

	sf::Vector2f newTarget = t_playerPos + t_playerVelocity * timePrediction;

	Seek newSeek;
	steering = newSeek.getSteering(t_currentPos, newTarget, t_rotation, t_velocity, t_playerVelocity);

	return steering;
}

sf::Keyboard::Key Pursue::getKey()
{
	return sf::Keyboard::Key::Num5;
}
