#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Behaviour.h"
#include "math.h"

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
	sf::Vector2f m_velocity;

	std::unique_ptr<Behaviour> m_behaviour;

public:
	Npc(std::unique_ptr<Behaviour> t_behaviour);

	void update(sf::Vector2f t_playerPos);
	void draw(sf::RenderWindow& t_window);

	void checkBoundary();
	void setBehaviour(std::unique_ptr<Behaviour> t_behaviour);
};