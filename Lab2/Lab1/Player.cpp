#include "Player.h"

Player::Player() : 
	m_texture("ASSETS//IMAGES//player.png"),
	m_sprite(m_texture)
{
	srand(time(NULL));

	m_sprite.setOrigin(sf::Vector2f(304.5f, 410.0f));
	m_sprite.setScale(sf::Vector2f(0.1f, 0.1f));

	std::cout << "x: " << m_sprite.getOrigin().x << " | y: " << m_sprite.getOrigin().y;

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
}

void Player::update(sf::Time t_deltaTime)
{
	checkInputs();

	m_position.x = m_circle.getPosition().x + cos(m_rotation * (M_PI / 180.0f)) * m_speed;
	m_position.y = m_circle.getPosition().y + sin(m_rotation * (M_PI / 180.0f)) * m_speed;

	checkBoundary();

	m_circle.setPosition(m_position);
	m_front.setPosition(m_position);
	m_sprite.setPosition(m_position);

	m_front.setRotation(sf::Angle(sf::degrees(m_rotation)));
	m_sprite.setRotation(sf::Angle(sf::degrees(m_rotation)));
	//std::cout << m_rotation << std::endl;
}

void Player::draw(sf::RenderWindow& t_window)
{
	//t_window.draw(m_circle);
	//t_window.draw(m_front);
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

sf::Vector2f Player::getPosition()
{
	return m_position;
}
