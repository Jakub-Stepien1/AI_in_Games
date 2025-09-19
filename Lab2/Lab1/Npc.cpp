#include "Npc.h"

Npc::Npc() :
	m_texture("ASSETS//IMAGES//enemy1.png"),
	m_sprite(m_texture)
{
	m_sprite.setOrigin(sf::Vector2f(208.0f,420.0f));
	m_sprite.setScale(sf::Vector2f(0.15f, 0.15f));

	int xPos = rand() % 800 + 1;
	int yPos = rand() % 600 + 1;

	m_speed = 2.0f;
	m_direction = rand() % 4 + 1;
	m_position = sf::Vector2f(xPos, yPos);

	m_circle.setRadius(20.0f);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setPosition(m_position);

	m_sprite.setPosition(m_position);
}

void Npc::update()
{
	if (m_direction == 1) // Up
	{
		m_rotation = 270.0f;
		m_position.y -= m_speed;
	}
	else if (m_direction == 2) // Right
	{
		m_rotation = 0.0f;
		m_position.x += m_speed;
	}
	else if (m_direction == 3) // Down
	{
		m_rotation = 90.0f;
		m_position.y += m_speed;
	}
	else if (m_direction == 4) // Left
	{
		m_rotation = 180.0f;
		m_position.x -= m_speed;
	}

	checkBoundary();

	m_sprite.setPosition(m_position);
	m_circle.setPosition(m_position);

	m_sprite.setRotation(sf::Angle(sf::degrees(m_rotation)));
}

void Npc::draw(sf::RenderWindow& t_window)
{
	//t_window.draw(m_circle);
	t_window.draw(m_sprite);
}

void Npc::checkBoundary()
{
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
}