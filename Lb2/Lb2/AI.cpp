#include "AI.h"

AI::AI(sf::Vector2f position, const sf::Texture& texture) : bodyTexture(texture)
{
	visionCone = new VisionCone(position);

	body.setTexture(texture);
	body.setPosition(position);

}

void AI::update(double dt)
{
	visionCone->updateVisionCone(body.getPosition());
}

void AI::render(sf::RenderWindow& window)
{
	window.draw(body);
	visionCone->renderVisionCone(window);
}

