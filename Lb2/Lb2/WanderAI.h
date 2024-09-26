#pragma once
#include "AI.h"


class WanderAI : public AI
{
public:
	WanderAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position);
	virtual ~WanderAI() {};

	void update(double dt, Player*player) override;

private:
	void move(double dt);
	void handleRandomDirection();

	float randomAngle = std::rand() % 181 - 90;
	sf::Vector2f velocity;
	float maxSpeed{ 80.f };

	sf::Vector2f m_steering;
	sf::Vector2f acceleration;

	sf::Vector2f target;

	sf::Clock changeWanderTimer;
};

