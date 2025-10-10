#include "Player.h"

Player::Player() : 
	m_texture("ASSETS//IMAGES//player.png"),
	m_sprite(m_texture)
{
	srand(time(NULL));

	m_sprite.setOrigin(sf::Vector2f(304.5f, 410.0f));
	m_sprite.setScale(sf::Vector2f(0.08f, 0.08f));

	m_velocity = sf::Vector2f(0.0f, 0.0f);
	m_speed = 0.0f;
	m_rotation = 0.0f;
	m_position = sf::Vector2f(100.0f, 100.0f);

	m_circle.setRadius(20.0f);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	m_circle.setFillColor(sf::Color::Green);
	m_circle.setPosition(m_position);

	m_front.setRadius(5.0f);
	m_front.setOrigin(sf::Vector2f(-25.0f, 5.0f));
	m_front.setFillColor(sf::Color::Blue);
	m_front.setPosition(m_position);

	m_visionCone.setPointCount(3);
	m_visionCone.setFillColor(sf::Color(0,255,0, 60));
	
	updateVisionCone();
}

void Player::update(sf::Time t_deltaTime)
{
	checkInputs();

	m_velocity = sf::Vector2f(cos(m_rotation * (M_PI / 180.0f)), sin(m_rotation * (M_PI / 180.0f))) * m_speed;

	m_position = m_circle.getPosition() + m_velocity;

	checkBoundary();
	updateVisionCone();

	m_circle.setPosition(m_position);
	m_front.setPosition(m_position);
	m_sprite.setPosition(m_position);

	m_front.setRotation(sf::Angle(sf::degrees(m_rotation)));
	m_sprite.setRotation(sf::Angle(sf::degrees(m_rotation)));
}

void Player::draw(sf::RenderWindow& t_window)
{
	//t_window.draw(m_circle);
	//t_window.draw(m_front);
	t_window.draw(m_visionCone);
	t_window.draw(m_sprite);
}

void Player::checkInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		m_speed += 0.1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		m_speed -= 0.1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_rotation -= 2.0f;
		if (m_rotation < 0.0f)
		{
			m_rotation = 359.0f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_rotation += 2.0f;
		if (m_rotation > 359.0f)
		{
			m_rotation = 0.0f;
		}
	}

	m_speed = std::clamp(m_speed, 0.0f, 5.0f);
}

void Player::checkBoundary()
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

void Player::updateVisionCone()
{
	float visionAngle = 45.0f; // in degrees
	float visionLength = 150.0f;
	float leftAngle = (m_rotation - visionAngle / 2.0f) * (M_PI / 180.0f); // in radians
	float rightAngle = (m_rotation + visionAngle / 2.0f) * (M_PI / 180.0f); // in radians
	
	m_visionCone.setPoint(0, m_position); // First point at player position
	m_visionCone.setPoint(1, m_position + sf::Vector2f(cos(leftAngle), sin(leftAngle)) * visionLength); // Second point at left corner
	m_visionCone.setPoint(2, m_position + sf::Vector2f(cos(rightAngle), sin(rightAngle)) * visionLength); // Third point at right corner
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

float Player::getRotation()
{
	return m_rotation;
}
