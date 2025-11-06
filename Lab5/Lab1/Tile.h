#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Tile
{
public:
	Tile(sf::Font& t_font);
	~Tile();

	void draw(sf::RenderWindow& t_window);

	bool isGoal();
	bool isStart();
	bool isVisited();

	void hover();
	void unhover();
	void setGoal();
	void setStart();
	void setVisited(bool t_visited);
	void clearTile();
	void showCost();
	void setColour(sf::Color t_color);

	int getCost();
	void setCost(int t_newCost);

	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();

private:

	sf::RectangleShape m_shape;

	sf::Font& m_font;
	sf::Text m_costText;

	bool m_goal;
	bool m_start;
	bool m_showCost;
	bool m_showVector;
	bool m_visited;
	bool m_path;

	int m_distanceToGoal;

};