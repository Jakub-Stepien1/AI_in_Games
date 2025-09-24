#include "Npc.h"

Npc::Npc(std::unique_ptr<Behaviour> t_behaviour) :
	m_texture("ASSETS//IMAGES//enemy1.png"),
	m_sprite(m_texture)
{
	m_sprite.setOrigin(sf::Vector2f(208.0f,420.0f));
	m_sprite.setScale(sf::Vector2f(0.15f, 0.15f));

	int xPos = rand() % 800 + 1;
	int yPos = rand() % 600 + 1;
	m_position = sf::Vector2f(xPos, yPos);

	m_speed = 2.0f;
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_circle.setRadius(20.0f);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setPosition(m_position);

	m_sprite.setPosition(m_position);

	m_behaviour = std::move(t_behaviour);
}

void Npc::update(sf::Vector2f t_playerPos)
{	
	m_velocity = m_behaviour->getSteering(m_position, t_playerPos) * m_speed;
	m_position += m_velocity;

	checkBoundary();

	m_sprite.setPosition(m_position);
	m_circle.setPosition(m_position);

	m_rotation = atan2(m_velocity.y, m_velocity.x) * 180.0f / M_PI;
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

void Npc::setBehaviour(std::unique_ptr<Behaviour> t_behaviour)
{
	m_behaviour = std::move(t_behaviour); 
}