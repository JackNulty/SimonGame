/// <summary>
/// @author Jack Nulty
/// @date January 2022
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_redButton{sf::Vector2f {200.0f, 200.0f}},
	m_blueButton{sf::Vector2f {200.0f, 200.0f}},
	m_greenButton{sf::Vector2f {200.0f, 200.0f}},
	m_yellowButton{sf::Vector2f{200.0f, 200.0f}},
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	buttonSetup(); // load buttons
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
	const float fps{ 30.0f };
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
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	switch (m_currentGame)
	{
	case GameMode::Start:
		startingUpdate();
		break;
	case GameMode::Showing:
		showingUpdate();
		break;
	case GameMode::Recieving:
		recievingUpdate();
		break;
	case GameMode::GameOver:
		overUpdate();
		break;
	default:
		break;
	}
	// reset buttons
	resetButtons();
}

void Game::resetButtons()
{
	m_bluePressed = false;
	m_redPressed = false;
	m_yellowPressed = false;
	m_greenPressed = false;
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.draw(m_redButton);
	m_window.draw(m_blueButton);
	m_window.draw(m_greenButton);
	m_window.draw(m_yellowButton);

	m_window.draw(m_simonTitle);
	if (GameMode::Start == m_currentGame)
	{
		m_window.draw(m_redText);
		m_window.draw(m_blueText);
		m_window.draw(m_greenText);
		m_window.draw(m_yellowText);
	}

	m_window.draw(m_fillerText);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_gameFont.loadFromFile("ASSETS\\FONTS\\impact.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	
	//title text
	m_simonTitle.setFont(m_gameFont);
	m_simonTitle.setFillColor(WHITE);
	m_simonTitle.setCharacterSize(64);
	m_simonTitle.setPosition(50.0f, 30.0f);
	m_simonTitle.setString("S I M O N");

	// instruction text
	m_redText.setFont(m_gameFont);
	m_redText.setFillColor(RED);
	m_redText.setCharacterSize(32);
	m_redText.setPosition(50, 200);
	m_redText.setString("Press red for \nmedium mode");

	m_greenText.setFont(m_gameFont);
	m_greenText.setFillColor(GREEN);
	m_greenText.setCharacterSize(32);
	m_greenText.setPosition(50, 100);
	m_greenText.setString("Press green for \neasy mode");

	m_yellowText.setFont(m_gameFont);
	m_yellowText.setFillColor(YELLOW);
	m_yellowText.setCharacterSize(32);
	m_yellowText.setPosition(50, 300);
	m_yellowText.setString("Press yellow for \nhard mode");

	m_blueText.setFont(m_gameFont);
	m_blueText.setFillColor(BLUE);
	m_blueText.setCharacterSize(32);
	m_blueText.setPosition(50, 400);
	m_blueText.setString("Press blue to\n exit game");

	//status text
	m_fillerText.setFont(m_gameFont);
	m_fillerText.setFillColor(WHITE);
	m_fillerText.setCharacterSize(22);
	m_fillerText.setPosition(500, 453);
	m_fillerText.setString("");

}

void Game::buttonSetup()
{
	// buttons showing on screen
	m_redButton.setFillColor(RED);
	m_redButton.setPosition( sf::Vector2f(570.0f,30.0f) );

	m_blueButton.setFillColor(BLUE);
	m_blueButton.setPosition(sf::Vector2f(570.0f, 250.0f));

	m_greenButton.setFillColor(GREEN);
	m_greenButton.setPosition(sf::Vector2f(350.0f, 30.0f));

	m_yellowButton.setFillColor(YELLOW);
	m_yellowButton.setPosition(sf::Vector2f(350.0f, 250.0f));

	//setup sound for tone
	if (!m_buffer.loadFromFile("ASSETS\\AUDIO\\tone.wav"))
	{
		std::cout << "Audio not loaded properly" << std::endl;
	}
	m_redTone.setBuffer(m_buffer);
	m_blueTone.setBuffer(m_buffer);
	m_yellowTone.setBuffer(m_buffer);
	m_greenTone.setBuffer(m_buffer);
	m_redTone.setPitch(0.75f);
	m_yellowTone.setPitch(0.5f);
	m_greenTone.setPitch(0.25f);

}

void Game::processGameEvents(sf::Event& event)
{
	const int COL_1_LEFT = 350;
	const int COL_1_RIGHT = 550;
	const int COL_2_LEFT = 570;
	const int COL_2_RIGHT = 770;
	const int ROW_1_TOP = 20;
	const int ROW_1_BOTTOM = 230;
	const int ROW_2_TOP = 250;
	const int ROW_2_BOTTOM = 450;

	// mouse release
	if (sf::Event::MouseButtonReleased == event.type)
	{
		//check all constants
		if (event.mouseButton.x > COL_1_LEFT && event.mouseButton.x < COL_1_RIGHT)
		{
			//row check
			if (event.mouseButton.y > ROW_1_TOP && event.mouseButton.y < ROW_1_BOTTOM)
			{
				m_greenPressed = true;
			}
			if (event.mouseButton.y > ROW_2_TOP && event.mouseButton.y < ROW_2_BOTTOM)
			{
				m_yellowPressed = true;
			}
		}
		if (event.mouseButton.x > COL_2_LEFT && event.mouseButton.x < COL_2_RIGHT)
		{
			if (event.mouseButton.y > ROW_1_TOP && event.mouseButton.y < ROW_1_BOTTOM)
			{
				m_redPressed = true;
			}
			if (event.mouseButton.y > ROW_2_TOP && event.mouseButton.y < ROW_2_BOTTOM)
			{
				m_bluePressed = true;
			}
		}
	}
}
