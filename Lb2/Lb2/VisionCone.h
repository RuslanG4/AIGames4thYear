#pragma once
#include<SFML/Graphics.hpp>
class VisionCone
{
public:
	VisionCone(sf::Vector2f position);
	void updateVisionCone(sf::Vector2f position);
	void renderVisionCone(sf::RenderWindow& window);
	void setVisionConeRotation(float angle);
private:
	sf::ConvexShape visionConeShape;
};

