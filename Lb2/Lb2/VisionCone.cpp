#include "VisionCone.h"

VisionCone::VisionCone(sf::Vector2f position)
{
	visionConeShape.setPointCount(4);

	visionConeShape.setPoint(0, position);
	visionConeShape.setPoint(1, sf::Vector2f(position.x - 50, position.y - 200));
	visionConeShape.setPoint(2, sf::Vector2f(position.x, position.y - 200));
	visionConeShape.setPoint(3, sf::Vector2f(position.x + 50, position.y - 200));

	visionConeShape.setOrigin(position);

	visionConeShape.setFillColor(sf::Color(255, 0, 0, 120));
}

void VisionCone::updateVisionCone(sf::Vector2f position)
{
	visionConeShape.setPosition(position);
}

void VisionCone::renderVisionCone(sf::RenderWindow& window)
{
	window.draw(visionConeShape);
}

void VisionCone::setVisionConeRotation(float angle)
{
	visionConeShape.setRotation(angle);
}

void VisionCone::detectPlayer(sf::RectangleShape playerSprite)
{
	if(playerSprite.getGlobalBounds().intersects(visionConeShape.getGlobalBounds()))
	{
		visionConeShape.setFillColor(sf::Color(0, 255, 0, 120));
	}
	else
	{
		visionConeShape.setFillColor(sf::Color(255, 0, 0, 120));
	}
}
