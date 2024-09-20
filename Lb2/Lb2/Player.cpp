#include "Player.h"

Player::Player()
{
	init();
}

void Player::update(double dt)
{
	move(dt);

	handleKeyInput();

	m_speed = std::clamp(m_speed, MAX_REVERSE_SPEED, MAX_FORWARD_SPEED);
	m_speed = m_speed * 0.995;

	//constantly rotates and sets rotation
	body.setRotation(m_rotation);
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::init()
{
	body.setRadius(50.f);
	body.setFillColor(sf::Color::Green);
}

void Player::handleKeyInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
}

void Player::move(double dt)
{
	newpos.x = body.getPosition().x + std::cos(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);
	newpos.y = body.getPosition().y + std::sin(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);

	body.setPosition(newpos);
}

void Player::increaseSpeed()
{
	m_speed += 1;
}

void Player::decreaseSpeed()
{
	m_speed -= 1;
}

void Player::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}
