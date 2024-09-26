#include "PursueAI.h"

PursueAI::PursueAI(AITypes type, sf::Texture& texture, sf::Vector2f t_position) : AI(type,t_position,texture)
{
}

void PursueAI::update(double dt, Player* player)
{
	if (isActive) {
		AI::update(dt, player);
		move(dt, player);
	}
}

void PursueAI::move(double dt, Player* player)
{
	target = player->getSprite().getPosition() - AI::getSprite().getPosition();

	float timeToReach = Utility::magnitude(target.x, target.y) / maxSpeed;
	sf::Vector2f playerVel;

	if(Utility::magnitude(player->getVelocity().x , player->getVelocity().y) <= 0)
	{
		playerVel = sf::Vector2f(0,0);
	}
	else
	{
		playerVel = Utility::unitVector2D(player->getVelocity());
	}

	sf::Vector2f predictedPosition = player->getSprite().getPosition() + playerVel * timeToReach * maxSpeed;
	sf::Vector2f desiredPath =AI::getSprite().getPosition() - predictedPosition;

	if (Utility::magnitude(desiredPath.x, desiredPath.y) < 200.f)
	{
		maxSpeed = maxSpeed * 0.985;
	}
	else
	{
		maxSpeed = originalMaxSpeed;
	}

	m_steering += Utility::unitVector2D(desiredPath);
	m_steering = Utility::truncate(m_steering, 20.f);
	acceleration = m_steering / 5.f;

	velocity = Utility::truncate(velocity + acceleration, maxSpeed);

	double speed = Utility::magnitude(velocity.x, velocity.y);

	sf::Vector2f newPos(AI::getSprite().getPosition().x + std::cos(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000),
		AI::getSprite().getPosition().y + std::sin(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000));

	auto dest = atan2(velocity.y, velocity.x) / Utility::PI * 180 + 180;

	AI::setPosition(newPos);
	handleRotation(dt, velocity, dest);

}

void PursueAI::handleRotation(double dt, sf::Vector2f velocity, float CurrAngle)
{
	auto currentRotation = getRotation();
	int newRotation;
	float angleDiff = std::fmod((CurrAngle - currentRotation + 360.f), 360.f);  //normalize

	// if > 180, rotate clockwise
	if (angleDiff > 180.f) {
		angleDiff -= 360.f;
	}

	float rotationSpeed = 2.f;
	if (std::abs(angleDiff) > rotationSpeed) {
		if (angleDiff > 0) {
			newRotation = static_cast<int>(currentRotation + rotationSpeed) % 360;
		}
		else {
			newRotation = static_cast<int>(currentRotation - rotationSpeed + 360) % 360;
		}
	}
	else {
		//jitter control
		newRotation = static_cast<int>(CurrAngle) % 360;
	}

	setPursueRotation(newRotation);
}
