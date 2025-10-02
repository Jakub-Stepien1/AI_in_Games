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

	m_maxSpeed = 3.0f;
	m_maxRotation = 180.0f;
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_active = false;
	m_isKeyHeld = false;

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
	case sf::Keyboard::Key::Num5:
		m_text.setString("Pursue");
		break;
	case sf::Keyboard::Key::Num6:
		m_text.setString("Swarm");
		m_sprite.setScale(sf::Vector2f(0.08f, 0.08f));
		break;
	default:
		break;
	}

	m_text.setCharacterSize(16);
	m_text.setFillColor(sf::Color::Black);
	m_text.setOrigin(m_text.getGlobalBounds().getCenter());
	m_text.setPosition(sf::Vector2f(m_position.x, m_position.y + 40.0f));

	m_circle.setRadius(20.0f);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setPosition(m_position);

	m_headingLine.setSize(sf::Vector2f(200.0f, 1.0f));
	m_headingLine.setOrigin(sf::Vector2f(0.0f, 0.5f));
	m_headingLine.setPosition(m_position);
	m_headingLine.setFillColor(sf::Color::Black);

	m_visionAngle = 45.0f; // in degrees
	m_visionLength = 200.0f;
	m_leftAngle = (m_rotation - m_visionAngle / 2.0f) * (M_PI / 180.0f); // in radians
	m_rightAngle = (m_rotation + m_visionAngle / 2.0f) * (M_PI / 180.0f); // in radians

	m_visionCone.setPointCount(3);
	m_visionCone.setFillColor(sf::Color(0, 0, 255, 60));

	updateVisionCone();

	m_sprite.setPosition(m_position);
}

void Npc::update(sf::Vector2f t_playerPos, sf::Vector2f t_playerVelocity, sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(m_behaviour->getKey()) && !m_isKeyHeld)
	{
		m_isKeyHeld = true;
		m_active = !m_active;
	}
	if (m_active)
	{
		SteeringOutput steering = m_behaviour->getSteering(m_position, t_playerPos, m_rotation, m_velocity, t_playerVelocity);

		m_velocity = m_velocity + steering.linear * t_deltaTime.asSeconds();
		m_orientation = m_orientation + steering.angular * t_deltaTime.asSeconds();

		if (m_velocity.length() > m_maxSpeed)
		{
			m_velocity = m_velocity.normalized() * m_maxSpeed;
		}
		if (m_orientation > m_maxRotation)
		{
			m_orientation = m_maxRotation;
		}
		else if (-m_orientation > m_maxRotation)
		{
			m_orientation = -m_maxRotation;
		}
		m_position += m_velocity; //* t_deltaTime.asSeconds();
		m_rotation += m_orientation;//* t_deltaTime.asSeconds();

		//m_velocity = m_behaviour->getSteering(m_position, t_playerPos, m_rotation, m_velocity, t_playerVelocity) * m_speed;
		//m_position += m_velocity;

		checkBoundary();
		updateVisionCone();
		
		if (isPlayerInVisionCone(t_playerPos))
		{
			m_visionCone.setFillColor(sf::Color(255, 0, 0, 60));
		}
		else
		{
			m_visionCone.setFillColor(sf::Color(0, 0, 255, 60));
		}

		m_sprite.setPosition(m_position);
		m_circle.setPosition(m_position);
		m_text.setPosition(sf::Vector2f(m_position.x, m_position.y + 40.0f));
		m_headingLine.setPosition(m_position);

		m_sprite.setRotation(sf::Angle(sf::degrees(m_rotation)));
		m_headingLine.setRotation(sf::Angle(sf::degrees(m_rotation)));
	}
	if (!sf::Keyboard::isKeyPressed(m_behaviour->getKey()))
	{
		m_isKeyHeld = false;
	}
}

void Npc::draw(sf::RenderWindow& t_window)
{
	if (m_active)
	{
		//t_window.draw(m_circle);
		if (m_behaviour->getKey() != sf::Keyboard::Key::Num6)
		{
			t_window.draw(m_visionCone);
			t_window.draw(m_headingLine);
		}

		t_window.draw(m_sprite);
		t_window.draw(m_text);
	}
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

void Npc::updateVisionCone()
{
	m_leftAngle = (m_rotation - m_visionAngle / 2.0f) * (M_PI / 180.0f); // in radians
	m_rightAngle = (m_rotation + m_visionAngle / 2.0f) * (M_PI / 180.0f); // in radians
	
	m_visionCone.setPoint(0, m_position); // First point at NPC position
	m_visionCone.setPoint(1, m_position + sf::Vector2f(cos(m_leftAngle), sin(m_leftAngle)) * m_visionLength); // Second point at left corner
	m_visionCone.setPoint(2, m_position + sf::Vector2f(cos(m_rightAngle), sin(m_rightAngle)) * m_visionLength); // Third point at right corner
}

bool Npc::isPlayerInVisionCone(sf::Vector2f t_playerPos)
{
	bool isInCone = false;

	sf::Vector2f toPlayer = t_playerPos - m_position;
	float distanceToPlayer = toPlayer.length();

	if (distanceToPlayer > m_visionLength)
	{
		isInCone = false;
	}
	else
	{
		float angleToPlayer = atan2(toPlayer.y, toPlayer.x);
		angleToPlayer = angleToPlayer * (180.0f / M_PI);
		float angleDifference = angleToPlayer - m_rotation;

		while (angleDifference > 180) // while loops to keep the angle difference in the right range, prevents issues with wrapping
		{
			angleDifference -= 180;
		}
		while (angleDifference < -180)
		{
			angleDifference += 180;
		}

		if (angleDifference < m_visionAngle / 2.0f && angleDifference > -m_visionAngle / 2.0f) // If player is within the range of the vision cone
		{
			isInCone = true;
		}
	}

	return isInCone;
}

void Npc::calcLJ(sf::Vector2f t_otherNpcPos)
{
	float attractionStrength = 20.0f;
	float repulsionStrength = 140.0f;
	float attractionAttenuation = 0.4f;
	float repulsionAttenuation = 0.8f;

	sf::Vector2f direction = m_position - t_otherNpcPos;
	float distance = direction.length();

	float potential = -(attractionStrength / pow(distance, attractionAttenuation)) + (repulsionStrength / pow(distance, repulsionAttenuation));

	if (distance < 0.01f)
	{
		return;
	}
	direction = direction.normalized();

	m_velocity += direction * potential;
}

void Npc::setBehaviour(std::unique_ptr<Behaviour> t_behaviour)
{
	m_behaviour = std::move(t_behaviour); 
}

sf::Vector2f Npc::getPosition()
{
	return m_position;
}