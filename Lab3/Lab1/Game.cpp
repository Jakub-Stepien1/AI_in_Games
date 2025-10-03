//Name: Jakub Stepien

#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{800U, 600U}, 32U }, "SFML Game 3.0" },
	m_DELETEexitGame{false}, //when true game will exit
	m_seekNpc(std::make_unique<Seek>()),
	m_arriveSlowNpc(std::make_unique<ArriveSlow>()),
	m_arriveFastNpc(std::make_unique<ArriveFast>()),
	m_wanderNpc(std::make_unique<Wander>()),
	m_pursueNpc(std::make_unique<Pursue>()),
	m_gameText(m_jerseyFont)
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	m_player.update(t_deltaTime);

	m_seekNpc.update(m_player.getPosition(), m_player.getVelocity(), t_deltaTime);
	m_arriveSlowNpc.update(m_player.getPosition(), m_player.getVelocity(), t_deltaTime);
	m_arriveFastNpc.update(m_player.getPosition(), m_player.getVelocity(), t_deltaTime);
	m_wanderNpc.update(m_player.getPosition(), m_player.getVelocity(), t_deltaTime);
	m_pursueNpc.update(m_player.getPosition(), m_player.getVelocity(), t_deltaTime);

	for (Npc* npc : m_swarmNpcs)
	{
		for (Npc* otherNpc : m_swarmNpcs)
		{
			if (npc != otherNpc)
			{
				npc->calcLJ(otherNpc->getPosition());
			}
		}
		npc->update(m_player.getPosition(), m_player.getVelocity(), t_deltaTime);
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_gameText);
	m_seekNpc.draw(m_window);
	m_arriveSlowNpc.draw(m_window);
	m_arriveFastNpc.draw(m_window);
	m_wanderNpc.draw(m_window);
	m_pursueNpc.draw(m_window);

	for (Npc* npc : m_swarmNpcs)
	{
		npc->draw(m_window);
	}

	m_player.draw(m_window);
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_gameText.setCharacterSize(20);
	m_gameText.setFillColor(sf::Color::Black);
	m_gameText.setString("You can toggle the active Npc's by pressing 1-5\nYou can toggle the swarm by pressing 6");

	for (int i = 0; i < 50; i++)
	{
		Npc* newNpc = new Npc(std::make_unique<Swarm>());
		m_swarmNpcs.push_back(newNpc);
	}

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{

}

/// <summary>
/// load sound file and assign buffers
/// </summary>
void Game::setupAudio()
{

}
