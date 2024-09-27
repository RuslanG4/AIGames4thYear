#include "VisionCone.h"

#include <iostream>

#include "Utility.h"

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

void VisionCone::setVisionConeRotation(float angle)
{
	visionConeShape.setRotation(angle);
}

void VisionCone::detectPlayer(sf::Vector2f obj1, sf::Vector2f obj2, sf::Vector2f coneDir)
{
	sf::Vector2f direction = obj1 - obj2;

	sf::Vector2f normToEnemy = Utility::unitVector2D(direction);
	sf::Vector2f normConeDir = Utility::unitVector2D(coneDir);

	float dotPord = Utility::dotProduct(normToEnemy, normConeDir);

	float angleToEnemy = std::acos(dotPord);
	angleToEnemy = angleToEnemy * 180.f / Utility::PI;

	if(angleToEnemy <= (60 / 2) && Utility::magnitude(direction.x, direction.y) < 230.f )
	{
		visionConeShape.setFillColor(sf::Color(0, 255, 0, 120));
	}

	else
	{
		visionConeShape.setFillColor(sf::Color(255, 0, 0, 120));
	}
}
