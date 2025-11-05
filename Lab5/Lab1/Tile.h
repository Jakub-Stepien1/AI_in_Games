#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Tile
{
public:
	Tile();
	~Tile();

	void draw(sf::RenderWindow& t_window);

	bool isGoal();
	bool isStart();

	void hover();
	void unhover();
	void setGoal();
	void setStart();
	void clearTile();

	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();

private:

	sf::RectangleShape m_shape;

	bool goal;
	bool start;
	bool showCost;
	bool showVector;

	int distanceToGoal;

};