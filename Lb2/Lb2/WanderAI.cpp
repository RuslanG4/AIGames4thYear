#include "WanderAI.h"

WanderAI::WanderAI(const sf::Texture& texture, sf::Vector2f t_position) : AI(t_position, texture)
{
	velocity.x = static_cast<float>((std::rand() % 100 - 50) / 10.0);
	velocity.y = static_cast<float>((std::rand() % 100 - 50) / 10.0);
}

void WanderAI::update(double dt)
{
	AI::update(dt);
	move(dt);
	handleRandomDirection();
}

void WanderAI::move(double dt)
{
	target = AI::getAheadVector();

	m_steering += Utility::unitVector2D(target);
	m_steering = Utility::truncate(m_steering, 10.f);
	acceleration = m_steering / 5.f;

	velocity = Utility::truncate(velocity + acceleration, 50.f);

	double speed = Utility::magnitude(velocity.x, velocity.y);

	sf::Vector2f newPos(AI::getSprite().getPosition().x + std::cos(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000),
		AI::getSprite().getPosition().y + std::sin(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000));

	AI::setPosition(newPos);
	AI::setRotation(randomAngle);

}

void WanderAI::handleRandomDirection()
{
	if(changeWanderTimer.getElapsedTime().asSeconds() > 3.f)
	{
		randomAngle =  std::rand() % 181 - 90;
		changeWanderTimer.restart();
	}
}
