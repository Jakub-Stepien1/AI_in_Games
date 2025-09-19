#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Player
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::CircleShape m_circle;
	sf::CircleShape m_front;
	sf::Vector2f m_position;
	int m_rotation;
	float m_speed;


public:
	Player();

	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);

	void checkInputs();
	void checkBoundary();
};