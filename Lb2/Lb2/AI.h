#pragma once
#include<SFML/Graphics.hpp>
#include<functional>
#include<iostream>

#include"Utility.h"
#include "Constants.h"
#include"VisionCone.h"

class AI
{
public:
	AI(sf::Vector2f position, const sf::Texture & texture);
	void update(double dt);
	void render(sf::RenderWindow& window);

private:
	VisionCone* visionCone;
	sf::Texture bodyTexture;
	sf::Sprite body;
};

