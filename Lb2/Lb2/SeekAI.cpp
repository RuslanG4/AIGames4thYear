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
	target = player->getSprite().getPosition() - AI::getSprite().getPosition();

	float timeToReach = Utility::magnitude(target.x, target.y) / maxSpeed;
	std::cout << Utility::magnitude(target.x, target.y) << "\n";
	sf::Vector2f predictedPosition = player->getSprite().getPosition() + Utility::unitVector2D(player->getVelocity()) * timeToReach;

	m_steering += Utility::unitVector2D(predictedPosition);
	m_steering = Utility::truncate(m_steering, 20.f);
	acceleration = m_steering / 5.f;

	velocity = Utility::truncate(velocity + acceleration, maxSpeed);

	double speed = Utility::magnitude(velocity.x, velocity.y);

	sf::Vector2f newPos(AI::getSprite().getPosition().x + std::cos(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000),
		AI::getSprite().getPosition().y + std::sin(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000));

	auto dest = atan2(-1 * velocity.y, -1 * velocity.x) / Utility::PI * 180 + 180;

	AI::setPosition(newPos);
	AI::setPursueRotation(dest);
}
