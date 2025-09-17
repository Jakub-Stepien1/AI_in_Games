#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Npc
{
private:
	sf::CircleShape m_sprite;
	sf::Vector2f m_position;
	int m_direction;
	float m_speed;

public:
	Npc();

	void update();

	sf::CircleShape getSprite();
};