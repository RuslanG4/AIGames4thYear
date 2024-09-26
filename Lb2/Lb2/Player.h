#pragma once
#include<SFML/Graphics.hpp>
#include<functional>

#include"Utility.h"
#include "Constants.h"

class Player
{
public:
	Player(sf::Texture& texture);
	~Player() {};
	void update(double dt);
	void render(sf::RenderWindow& window);
	void init();

	sf::RectangleShape getSprite() const { return hitbox; };

	void handleKeyInput();
	void move(double dt);

	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();

	void boundary();

	sf::Vector2f getVelocity() { return newpos; };
private:
	sf::Sprite body;
	sf::Texture bodyTexture;

	sf::RectangleShape hitbox;

	double m_speed{ 0.0 };
	double m_rotation{ 0.0 };

	sf::Vector2f newpos;
	sf::Vector2f m_previousPosition;

	const double MAX_REVERSE_SPEED = -300; //for movement
	const double MAX_FORWARD_SPEED = 300;
};

