/// <summary>
/// author Jack Nulty
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class GameMode
{
	Showing,
	Recieving,
	GameOver,
	Start
};
const sf::Color RED{ 180,0,0,255 };
const sf::Color GREEN{ 0,180,0,255 };
const sf::Color BLUE{ 0,0,180,255 };
const sf::Color YELLOW{ 180,180,0,255 };
const sf::Color WHITE{ 255,255,255,255 };

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void buttonSetup();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_gameFont; // font used by message

	sf::RectangleShape m_redButton; // red rectangle used for the button
	sf::RectangleShape m_blueButton; // blue rectangle used for button
	sf::RectangleShape m_greenButton; // green rectangle used for button
	sf::RectangleShape m_yellowButton; // yellow rectangle used for button

	sf::Text m_simonTitle; // text used for title
	sf::Text m_redText; // text for red instructions
	sf::Text m_blueText; // text for blue instructions
	sf::Text m_greenText; // text for green instructions
	sf::Text m_yellowText; // text for yellow instructions
	sf::Text m_fillerText; // status text

	sf::SoundBuffer m_buffer; // buffer for tone
	sf::Sound m_redTone; // red sound
	sf::Sound m_blueTone; // blue sound
	sf::Sound m_yellowTone; // yellow sound
	sf::Sound m_greenTone; // green sound

	GameMode m_currentGame; // current mode of the game

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

