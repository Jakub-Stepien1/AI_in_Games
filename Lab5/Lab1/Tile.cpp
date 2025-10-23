#include "Tile.h"

Tile::Tile()
{
	distanceToGoal = 999;
	goal = false;
	start = false;

	m_shape.setFillColor(sf::Color(0,0,255,70));
	
	m_shape.setOutlineColor(sf::Color::White);

	m_shape.setSize(sf::Vector2f(15.0f, 15.0f));
	//m_shape.setOrigin(sf::Vector2f(7.5f, 7.5f));
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
}

bool Tile::isGoal()
{
	return goal;
}

void Tile::hover()
{
	m_shape.setFillColor(sf::Color(255, 0, 0, 70));
}

void Tile::unhover()
{
	m_shape.setFillColor(sf::Color(0, 0, 255, 70));
}

void Tile::setGoal()
{
	goal = true;
	m_shape.setFillColor(sf::Color(255, 0, 0, 120));
}

void Tile::setPosition(sf::Vector2f t_position)
{
	m_shape.setPosition(t_position);
}

sf::Vector2f Tile::getPosition()
{
	return m_shape.getPosition();
}