#include "Tile.h"

Tile::Tile(sf::Font& t_font) :
	m_font(t_font),
	m_costText(m_font)
{
	m_distanceToGoal = 999;
	m_goal = false;
	m_start = false;
	m_showCost = false;
	m_showVector = false;
	m_visited = false;

	m_shape.setFillColor(sf::Color(0,0,255,70));
	
	m_shape.setOutlineColor(sf::Color::White);

	m_shape.setSize(sf::Vector2f(15.0f, 15.0f));
	//m_shape.setOrigin(sf::Vector2f(7.5f, 7.5f));

	m_costText.setCharacterSize(10);
	m_costText.setFillColor(sf::Color::Black);
	m_costText.setString(std::to_string(m_distanceToGoal));
	m_costText.setOrigin(m_costText.getGlobalBounds().getCenter());
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
	if (m_showCost)
	{
		t_window.draw(m_costText);
	}
}

bool Tile::isGoal()
{
	return m_goal;
}

bool Tile::isStart()
{
	return m_start;
}

bool Tile::isVisited()
{
	return m_visited;
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
	m_goal = true;
	m_start = false;
	m_shape.setFillColor(sf::Color(255, 0, 0, 120));
	m_distanceToGoal = 0;
	m_costText.setString(std::to_string(m_distanceToGoal));
	//m_costText.setOrigin(m_costText.getGlobalBounds().getCenter());
}

void Tile::setStart()
{
	m_start = true;
	m_goal = false;
	m_shape.setFillColor(sf::Color(0, 255, 0, 120));
}

void Tile::setVisited(bool t_visited)
{
	m_visited = t_visited;
}

void Tile::clearTile()
{
	if (m_start == false)
	{
		m_distanceToGoal = 999;
	}

	m_goal = false;
	m_start = false;
	m_visited = false;
	m_shape.setFillColor(sf::Color(0, 0, 255, 70));
	m_costText.setString(std::to_string(m_distanceToGoal));
}

void Tile::showCost()
{
	m_showCost = !m_showCost;
	m_showVector = false;
}

int Tile::getCost()
{
	return m_distanceToGoal;
}

void Tile::setCost(int t_newCost)
{
	m_distanceToGoal = t_newCost;
	m_costText.setString(std::to_string(m_distanceToGoal));
}

void Tile::setPosition(sf::Vector2f t_position)
{
	m_shape.setPosition(t_position);
	m_costText.setPosition(sf::Vector2f(t_position.x + 7.5f, t_position.y + 7.5f));
}

sf::Vector2f Tile::getPosition()
{
	return m_shape.getPosition();
}