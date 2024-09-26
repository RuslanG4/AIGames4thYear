#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" }
{
	initialise();
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
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if(sf::Event::KeyReleased == newEvent.type)
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
	editAIState();
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	player->update(t_deltaTime.asMilliseconds());
	for (auto enemy : enemies)
	{
		enemy->update(t_deltaTime.asMilliseconds(), player);
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	player->render(m_window);
	for(auto enemy : enemies)
	{
		enemy->render((m_window));
	}
	m_window.draw(text);
	m_window.display();
}

void Game::initialise()
{
	if(!fighterShipTexture.loadFromFile(FIGHTER_SHIP))
	{
		std::cout << "Error loading fighter ship texture";
	}
	if (!playerTexture.loadFromFile(PLAYER_SHIP))
	{
		std::cout << "Error loading player ship texture";
	}
	if(!font.loadFromFile(FONT))
	{
		std::cout << "error loading font";
	}
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString("1 : Wander        2 : Pursue          3 : Seek          4 : Slow Arrive          5 : Fast Arrive");

	player = new Player(playerTexture);

	enemies.push_back(new PursueAI(AITypes::Pursue, fighterShipTexture, sf::Vector2f(600, 600)));

	enemies.push_back(new WanderAI(AITypes::Wander,fighterShipTexture, sf::Vector2f(800, 600)));

	enemies.push_back(new SeekAI(AITypes::Seek, fighterShipTexture, sf::Vector2f(1000, 800)));

	enemies.push_back(new ArriveAI(AITypes::FastArrive, fighterShipTexture, sf::Vector2f(1200, 600), 350.f));

	enemies.push_back(new ArriveAI(AITypes::SlowArrive, fighterShipTexture, sf::Vector2f(1000, 200), 150.f));

}

void Game::editAIState()
{
	if(sf::Keyboard::isKeyPressed((sf::Keyboard::Num1)))
	{
		for(auto enemy : enemies)
		{
			if(enemy->getType() == AITypes::Wander)
			{
				enemy->setActive();
			}
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num2)))
	{
		for (auto enemy : enemies)
		{
			if (enemy->getType() == AITypes::Pursue)
			{
				enemy->setActive();
			}
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num3)))
	{
		for (auto enemy : enemies)
		{
			if (enemy->getType() == AITypes::Seek)
			{
				enemy->setActive();
			}
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num4)))
	{
		for (auto enemy : enemies)
		{
			if (enemy->getType() == AITypes::SlowArrive)
			{
				enemy->setActive();
			}
		}
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Num5)))
	{
		for (auto enemy : enemies)
		{
			if (enemy->getType() == AITypes::FastArrive)
			{
				enemy->setActive();
			}
		}
	}
}
