#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Player
{
private:
	sf::CircleShape m_sprite;
	sf::CircleShape m_front;
	sf::Vector2f m_position;
	int m_rotation;
	float m_speed;


public:
	Player();

	void update(sf::Time t_deltaTime);
	void checkInputs();
	void checkBoundary();

	void draw(sf::RenderWindow& t_window);
};