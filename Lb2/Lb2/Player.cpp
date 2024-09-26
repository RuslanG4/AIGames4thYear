#include "Player.h"

#include <iostream>

Player::Player(sf::Texture& texture)
{
	bodyTexture = texture;
	init();
}

void Player::update(double dt)
{
	move(dt);
	boundary();

	handleKeyInput();

	m_speed = std::clamp(m_speed, MAX_REVERSE_SPEED, MAX_FORWARD_SPEED);
	m_speed = m_speed * 0.995;

	//constantly rotates and sets rotation
	body.setRotation(m_rotation);
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(hitbox);
	//window.draw(shape);
}

void Player::init()
{
	body.setTexture(bodyTexture);
	body.setPosition(400, 400);
	body.setOrigin(64, 64);

	hitbox.setSize(sf::Vector2f(64, 64));
	hitbox.setOrigin(32, 32);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::White);
	hitbox.setOutlineThickness(2.f);

	shape.setRadius(15.f);
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(100,100);
	shape.setOrigin(15, 15);
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
	
	vel.x = std::cos(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);
	vel.y = std::sin(m_rotation * Utility::DEG_TO_RADIAN) * m_speed * (dt / 1000);

	newpos.x = body.getPosition().x + vel.x;
	newpos.y = body.getPosition().y + vel.y;

	body.setPosition(newpos);
	hitbox.setPosition(body.getPosition());

	//shape.setPosition(body.getPosition() + vel * 230.f);
}

void Player::increaseSpeed()
{
	m_speed += 15;
}

void Player::decreaseSpeed()
{
	m_speed -= 15;
}

void Player::increaseRotation()
{
	m_rotation += 3;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	m_rotation -= 3;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void Player::boundary()
{
	if(body.getPosition().x > SCREEN_WIDTH + boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(-boundaryBuffer, body.getPosition().y));
	}
	else if(body.getPosition().x<0 - boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(SCREEN_WIDTH + boundaryBuffer, body.getPosition().y));
	}
	else if(body.getPosition().y<0 - boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, SCREEN_HEIGHT + boundaryBuffer));
	}
	else if(body.getPosition().y>SCREEN_HEIGHT + boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, -boundaryBuffer));
	}
}
