#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include<vector>
#include"Constants.h"
#include"Player.h"
#include "AI.h"
#include"PursueAI.h"
#include"WanderAI.h"
#include <filesystem>


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
	void initialise();
	void editAIState();

	sf::RenderWindow m_window; // main SFML window

	std::vector<AI*> enemies;
	Player* player;

	sf::Texture fighterShipTexture;
	sf::Texture playerTexture;
};

#endif // !GAME_HPP