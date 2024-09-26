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
	m_steering = Utility::truncate(m_steering, 10.f);
	acceleration = m_steering / 1.f; //mass

	velocity = Utility::truncate(velocity + acceleration, maxSpeed);

	double speed = Utility::magnitude(velocity.x, velocity.y);

	auto dest = atan2(velocity.y, velocity.x) / Utility::PI * 180 + 180;
	if (dest < 0) {
		dest += 360;
	}
	handleRotation(dt, velocity, dest);

	sf::Vector2f newPos(AI::getSprite().getPosition().x + std::cos(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000),
		AI::getSprite().getPosition().y + std::sin(Utility::DEG_TO_RADIAN * AI::getRotation()) * speed * (dt / 1000));

	AI::setPosition(newPos);

}

void ArriveAI::handleRotation(double dt, sf::Vector2f velocity, float CurrAngle)
{
	auto currentRotation = getRotation();
	float newRotation;
	float angleDiff = std::fmod((CurrAngle - currentRotation + 360.f), 360.f);  //normalize

	// if > 180, rotate clockwise
	if (angleDiff > 180.f) {
		angleDiff -= 360.f;
	}

	float rotationSpeed = 4.f;

	if (std::abs(angleDiff) > 180.f) {
		rotationSpeed = 12.f;  // Speed up rotation if the angle is large
	}

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


