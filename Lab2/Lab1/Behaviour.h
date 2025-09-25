#pragma once

#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.h"

class Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity) = 0;
	virtual sf::Keyboard::Key getKey() = 0;

};

class Seek : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity) override;
	virtual sf::Keyboard::Key getKey() override;
};

class ArriveSlow : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity) override;
	virtual sf::Keyboard::Key getKey() override;
};

class ArriveFast : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity) override;
	virtual sf::Keyboard::Key getKey() override;
};

class Wander : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity) override;
	virtual sf::Keyboard::Key getKey() override;
};

class Pursue : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos, float& t_rotation, sf::Vector2f t_velocity, sf::Vector2f t_playerVelocity) override;
	virtual sf::Keyboard::Key getKey() override;
};