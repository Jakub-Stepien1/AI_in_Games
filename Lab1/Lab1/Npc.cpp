#include "Npc.h"

Npc::Npc()
{
	int xPos = rand() % 800 + 1;
	int yPos = rand() % 600 + 1;

	m_speed = 2.0f;
	m_direction = rand() % 4 + 1;
	m_position = sf::Vector2f(xPos, yPos);

	m_sprite.setRadius(20.0f);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getRadius(), m_sprite.getRadius()));
	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setPosition(m_position);
}

void Npc::update()
{
	if (m_direction == 1) // Up
	{
		m_position.y -= m_speed;
	}
	else if (m_direction == 2) // Right
	{
		m_position.x += m_speed;
	}
	else if (m_direction == 3) // Down
	{
		m_position.y += m_speed;
	}
	else if (m_direction == 4) // Left
	{
		m_position.x -= m_speed;
	}

	if (m_position.x > 820)
	{
		m_position.x = -20;
	}
	else if (m_position.x < -20)
	{
		m_position.x = 820;
	}

	if (m_position.y > 620)
	{
		m_position.y = -20;
	}
	else if (m_position.y < -20)
	{
		m_position.y = 620;
	}

	m_sprite.setPosition(m_position);
}

sf::CircleShape Npc::getSprite()
{
	return m_sprite;
}
