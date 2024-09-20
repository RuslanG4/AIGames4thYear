#pragma once
#include<SFML/Graphics.hpp>
#include<functional>

#include"Utility.h"

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
private:
	sf::CircleShape body;

	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };

	sf::Vector2f newpos;
	sf::Vector2f m_previousPosition;

	const double MAX_REVERSE_SPEED = -200; //for movement
	const double MAX_FORWARD_SPEED = 200;

};

