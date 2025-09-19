#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Npc
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::CircleShape m_circle;
	sf::Vector2f m_position;
	int m_direction;
	float m_rotation;
	float m_speed;

public:
	Npc();

	void update();
	void draw(sf::RenderWindow& t_window);

	void checkBoundary();
};