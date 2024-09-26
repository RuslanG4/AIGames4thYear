#pragma once
#include"AI.h"
#include"VisionCone.h"
#include<SFML/Graphics.hpp>
class PursueAI : public AI
{
public:
	PursueAI(AITypes type, sf::Texture & texture, sf::Vector2f t_position);
	virtual ~PursueAI() {};

	void update(double dt, Player* player) override;

private:
	void move(double dt, sf::Vector2f playerPos);

	sf::Vector2f velocity;
	float maxSpeed{ 180.f };

	sf::Vector2f m_steering;
	sf::Vector2f acceleration;

	sf::Vector2f target;

};

