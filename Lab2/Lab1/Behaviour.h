#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Behaviour
{
public:
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) = 0;
};

class Seek : public Behaviour
{
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) override;
};

class Wander : public Behaviour
{
	virtual sf::Vector2f getSteering(sf::Vector2f t_currentPos, sf::Vector2f t_playerPos) override;
};