#pragma once
#include"AI.h"
class SeekAI : public AI
{
public:
	SeekAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position);
	virtual ~SeekAI() {};

	void update(double dt, Player* player) override;

private:
	void move(double dt, Player* player);

	sf::Vector2f velocity;
	float maxSpeed{ 180.f };

	sf::Vector2f m_steering;
	sf::Vector2f acceleration;

	sf::Vector2f target;
};

