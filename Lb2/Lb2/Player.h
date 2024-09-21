#pragma once
#include<SFML/Graphics.hpp>
#include<functional>

#include"Utility.h"
#include "Constants.h"

class Player
{
public:
	Player();
	~Player() {};
	void update(double dt);
	void render(sf::RenderWindow& window);
	void init();

	void handleKeyInput();
	void move(double dt);

	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();

	void boundary();
private:
	sf::RectangleShape body{sf::Vector2f(80.f,40.f)};

	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };

	sf::Vector2f newpos;
	sf::Vector2f m_previousPosition;

	const double MAX_REVERSE_SPEED = -300; //for movement
	const double MAX_FORWARD_SPEED = 300;
};

