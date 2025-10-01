//Name: Jakub Stepien
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Npc.h"
#include "Behaviour.h"


const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	void setupSprites();
	void setupAudio();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_jerseyFont;// font used by message

	sf::Text m_gameText;
	
	bool m_DELETEexitGame; // control exiting game

	Player m_player;
	Npc m_seekNpc;
	Npc m_arriveSlowNpc;
	Npc m_arriveFastNpc;
	Npc m_wanderNpc;
	Npc m_pursueNpc;

	std::vector<Npc*> m_swarmNpcs;

};

#pragma warning( pop ) 
#endif // !GAME_HPP

