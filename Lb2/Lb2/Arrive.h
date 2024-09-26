#pragma once
#include"AI.h"
class ArriveAI : public AI
{
public:
	ArriveAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position, float maxSpeedVal);
	virtual ~ArriveAI() {};

	void update(double dt, Player* player) override;

private:
	void move(double dt, Player* player);
	void handleRotation(double dt, sf::Vector2f velocity, float CurrAngle);
	void slowDown(Player* player);

	sf::Vector2f velocity;
	float maxSpeed;
	float originalMaxSpeed;

	sf::Vector2f m_steering;
	sf::Vector2f acceleration;

	sf::Vector2f target;

};

