#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) = 0;
	virtual sf::Keyboard::Key getKey() = 0;

};

class Seek : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) override;
	virtual sf::Keyboard::Key getKey() override;
};

class ArriveSlow : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) override;
	virtual sf::Keyboard::Key getKey() override;
};

class ArriveFast : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) override;
	virtual sf::Keyboard::Key getKey() override;
};

class Wander : public Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) override;
};