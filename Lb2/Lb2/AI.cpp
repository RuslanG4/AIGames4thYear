#include "AI.h"

AI::AI(AITypes type, sf::Vector2f position, const sf::Texture& texture) : bodyTexture(texture)
{
	visionCone = new VisionCone(position);

	body.setTexture(texture);
	body.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	body.setScale(2, 2);
	body.setPosition(position);

	currentType = type;

}

void AI::update(double dt, Player* player)
{
	if (isActive) {
		visionCone->updateVisionCone(body.getPosition());
		visionCone->setVisionConeRotation(m_rotation);
		visionCone->detectPlayer(player->getSprite());
		points();
		calculateAheadVector();
		boundary();
	}
}

void AI::render(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(m_points);
	visionCone->renderVisionCone(window);
}

void AI::calculateAheadVector()
{
	auto headingRadians = (m_rotation - 90) * Utility::DEG_TO_RADIAN;
	sf::Vector2f headingVector(std::cos(headingRadians) * 200, std::sin(headingRadians) * 200);
	m_ahead = body.getPosition() + headingVector;
}

void AI::points()
{
	m_points.setPrimitiveType(sf::Lines); //sets line
	m_points.clear(); //only draws one line

	m_start.color = sf::Color::White;
	m_start.position = body.getPosition();    //start line at origin of ball
	m_points.append(m_start);

	sf::Vertex newVertrex;
	newVertrex.color = sf::Color::White;
	newVertrex.position.x = m_ahead.x;    //end line
	newVertrex.position.y = m_ahead.y;
	m_points.append(newVertrex);

}

void AI::boundary()
{
	if (body.getPosition().x > SCREEN_WIDTH + boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(-boundaryBuffer, body.getPosition().y));
	}
	else if (body.getPosition().x < 0 - boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(SCREEN_WIDTH + boundaryBuffer, body.getPosition().y));
	}
	else if (body.getPosition().y < 0 - boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, SCREEN_HEIGHT + boundaryBuffer));
	}
	else if (body.getPosition().y > SCREEN_HEIGHT + boundaryBuffer)
	{
		body.setPosition(sf::Vector2f(body.getPosition().x, -boundaryBuffer));
	}
}

