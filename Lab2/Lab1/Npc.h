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

	sf::Font m_font;
	sf::Text m_text;

	sf::Vector2f m_position;
	float m_rotation;
	float m_speed;
	sf::Vector2f m_velocity;
	bool m_active;
	bool m_isKeyHeld;

	std::unique_ptr<Behaviour> m_behaviour;

public:
	Npc(std::unique_ptr<Behaviour> t_behaviour);

	void update(sf::Vector2f t_playerPos, sf::Vector2f t_playerVelocity);
	void draw(sf::RenderWindow& t_window);

	void checkBoundary();

	void setBehaviour(std::unique_ptr<Behaviour> t_behaviour);
};