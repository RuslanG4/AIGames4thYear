#include "VisionCone.h"

VisionCone::VisionCone(sf::Vector2f position)
{
	visionConeShape.setPointCount(4);

	visionConeShape.setPoint(0, position);
	visionConeShape.setPoint(1, sf::Vector2f(position.x + 200, position.y - 50));
	visionConeShape.setPoint(2, sf::Vector2f(position.x + 200, position.y));
	visionConeShape.setPoint(3, sf::Vector2f(position.x + 200, position.y + 50));

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
