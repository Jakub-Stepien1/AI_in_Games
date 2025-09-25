#include "Npc.h"

Npc::Npc(std::unique_ptr<Behaviour> t_behaviour) :
	m_texture("ASSETS//IMAGES//enemy1.png"),
	m_sprite(m_texture),
	m_text(m_font)
{
	if (!m_font.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_behaviour = std::move(t_behaviour);

	m_sprite.setOrigin(sf::Vector2f(208.0f,420.0f));
	m_sprite.setScale(sf::Vector2f(0.15f, 0.15f));

	int xPos = rand() % 800 + 1;
	int yPos = rand() % 600 + 1;
	m_position = sf::Vector2f(xPos, yPos);

	switch (m_behaviour->getKey())
	{
	case sf::Keyboard::Key::Num1:
		m_text.setString("Seek");
		break;
	case sf::Keyboard::Key::Num2:
		m_text.setString("Arrive Slow");
		break;
	case sf::Keyboard::Key::Num3:
		m_text.setString("Arrive Fast");
		break;
	case sf::Keyboard::Key::Num4:
		m_text.setString("Wander");
		break;
	default:
		break;
	}

	m_speed = 2.0f;
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_active = false;
	m_isKeyHeld = false;

	m_text.setCharacterSize(16);
	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_text.getGlobalBounds().getCenter());
	m_text.setPosition(sf::Vector2f(m_position.x, m_position.y + 40.0f));

	m_circle.setRadius(20.0f);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setPosition(m_position);

	m_sprite.setPosition(m_position);
}

void Npc::update(sf::Vector2f t_playerPos)
{
	if (sf::Keyboard::isKeyPressed(m_behaviour->getKey()) && !m_isKeyHeld)
	{
		m_isKeyHeld = true;
		m_active = !m_active;
	}
	if (m_active)
	{
		m_rotation = m_sprite.getRotation().asDegrees();

		m_velocity = m_behaviour->getSteering(m_position, t_playerPos, m_rotation) * m_speed;
		m_position += m_velocity;

		checkBoundary();

		m_sprite.setPosition(m_position);
		m_circle.setPosition(m_position);
		m_text.setPosition(sf::Vector2f(m_position.x, m_position.y + 40.0f));

		//sf::Vector2f facePlayer = t_playerPos - m_position;
		//facePlayer = facePlayer.normalized();

		//m_rotation = atan2(facePlayer.y, facePlayer.x) * 180.0f / M_PI;
		m_sprite.setRotation(sf::Angle(sf::degrees(m_rotation)));
	}
	if (!sf::Keyboard::isKeyPressed(m_behaviour->getKey()))
	{
		m_isKeyHeld = false;
	}
}

void Npc::draw(sf::RenderWindow& t_window)
{
	//t_window.draw(m_circle);
	t_window.draw(m_sprite);
	t_window.draw(m_text);
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