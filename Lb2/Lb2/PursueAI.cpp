#include "PursueAI.h"

PursueAI::PursueAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position) : AI(type,t_position,texture)
{
}

void PursueAI::update(double dt, Player* player)
{
	if (isActive) {
		AI::update(dt, player);
		move(dt, player->getSprite().getPosition());
	}
}

void PursueAI::move(double dt, sf::Vector2f playerPos)
{
	target = AI::getSprite().getPosition() - playerPos;

	m_steering += Utility::unitVector2D(target);
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
