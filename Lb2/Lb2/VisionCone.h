#pragma once
#include<SFML/Graphics.hpp>
class VisionCone
{
public:
	VisionCone(sf::Vector2f position);
	void updateVisionCone(sf::Vector2f position);
	void renderVisionCone(sf::RenderWindow& window);
	void setVisionConeRotation(float angle);
	void detectPlayer(sf::Vector2f obj1, sf::Vector2f obj2, sf::Vector2f coneDir);
private:
	sf::ConvexShape visionConeShape;
};

