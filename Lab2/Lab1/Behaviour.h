#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Behaviour
{
public:
	virtual sf::Vector2f getSteering() = 0;
};

class Wander : Behaviour
{
	virtual sf::Vector2f getSteering() override;
};