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
	sf::ConvexShape m_visionCone;
	sf::RectangleShape m_headingLine;

	sf::Font m_font;
	sf::Text m_text;

	sf::Vector2f m_position;
	float m_rotation;
	float m_maxRotation;
	float m_orientation;

	float m_maxSpeed;
	sf::Vector2f m_velocity;
	bool m_active;
	bool m_isKeyHeld;

	float m_visionAngle;
	float m_visionLength;
	float m_leftAngle;
	float m_rightAngle;

	std::unique_ptr<Behaviour> m_behaviour;

public:
	Npc(std::unique_ptr<Behaviour> t_behaviour);

	void update(sf::Vector2f t_playerPos, sf::Vector2f t_playerVelocity, sf::Time t_deltaTime);
	void draw(sf::RenderWindow& t_window);

	void checkBoundary();
	void updateVisionCone();
	bool isPlayerInVisionCone(sf::Vector2f t_playerPos);
	void calcLJ(sf::Vector2f t_otherNpcPos);

	void setBehaviour(std::unique_ptr<Behaviour> t_behaviour);
	sf::Vector2f getPosition();
};