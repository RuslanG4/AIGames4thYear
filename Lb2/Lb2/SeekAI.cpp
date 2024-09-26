#include "SeekAI.h"

SeekAI::SeekAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position) : AI(type, t_position, texture)
{
}

void SeekAI::update(double dt, Player* player)
{
	if (isActive) {
		AI::update(dt, player);
		move(dt, player);
	}
}

void SeekAI::move(double dt, Player* player)
{
	target = AI::getSprite().getPosition() - player->getSprite().getPosition();

	m_steering += Utility::unitVector2D(target);
	m_steering = Utility::truncate(m_steering, 20.f);
	acceleration = m_steering / 5.f;

	velocity = Utility::truncate(velocity + acceleration, maxSpeed);

	double speed = Utility::magnitude(velocity.x, velocity.y);

	sf::Vector2f newPos(AI::getSprite().getPosition().x + std::cos(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000),
		AI::getSprite().getPosition().y + std::sin(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000));

	auto dest = atan2(-1 * velocity.y, -1 * velocity.x) / Utility::PI * 180 + 180;

	AI::setPosition(newPos);
	handleRotation(dt, velocity, dest);

	
}

void SeekAI::handleRotation(double dt, sf::Vector2f velocity, float CurrAngle)
{
	auto currentRotation = getRotation();
	int newRotation;

	if ((static_cast<int>(std::round(CurrAngle - currentRotation + 360))) % 360 > 180)
	{
		// rotate clockwise
		newRotation = static_cast<int>(getRotation()+1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		newRotation = static_cast<int>(getRotation() -1) % 360;
	}

	setPursueRotation(newRotation + 90);
}

