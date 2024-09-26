#include "Arrive.h"

ArriveAI::ArriveAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position, float maxSpeedVal) : AI(type, t_position, texture)
{
	originalMaxSpeed = maxSpeedVal;
	maxSpeed = originalMaxSpeed;
}

void ArriveAI::update(double dt, Player* player)
{
	if (isActive) {
		AI::update(dt, player);
		move(dt, player);
	}
}

void ArriveAI::move(double dt, Player* player)
{
	target = AI::getSprite().getPosition() - player->getSprite().getPosition();

	if (Utility::magnitude(target.x, target.y) < 200.f)
	{
		if (originalMaxSpeed < 250) {
			maxSpeed = maxSpeed * 0.985;
		}
		else {
			maxSpeed = maxSpeed * 0.9;
		}
	}
	else
	{
		maxSpeed = originalMaxSpeed;
	}

	m_steering += Utility::unitVector2D(target);
	m_steering = Utility::truncate(m_steering, 20.f);
	acceleration = m_steering / 5.f;

	velocity = Utility::truncate(velocity + acceleration, maxSpeed);

	double speed = Utility::magnitude(velocity.x, velocity.y);

	std::cout << Utility::magnitude(target.x, target.y)<<"\n";

	sf::Vector2f newPos(AI::getSprite().getPosition().x + std::cos(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000),
		AI::getSprite().getPosition().y + std::sin(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000));

	auto dest = atan2(-1 * velocity.y, -1 * velocity.x) / Utility::PI * 180 + 180;

	AI::setPosition(newPos);
	handleRotation(dt, velocity, dest);
	//AI::setPursueRotation(dest);

}

void ArriveAI::handleRotation(double dt, sf::Vector2f velocity, float CurrAngle)
{
	auto currentRotation = getRotation();
	int newRotation;

	if ((static_cast<int>(std::round(CurrAngle - currentRotation + 360))) % 360 > 180)
	{
		// rotate clockwise
		newRotation = static_cast<int>(getRotation() + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		newRotation = static_cast<int>(getRotation() - 1) % 360;
	}

	setPursueRotation(newRotation + 90);
}


