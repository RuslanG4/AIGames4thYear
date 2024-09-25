#pragma once
#include"AI.h"
#include"VisionCone.h"
#include<SFML/Graphics.hpp>
class PursueAI : public AI
{
public:
	PursueAI(AITypes type, sf::Texture & texture, sf::Vector2f t_position);
	virtual ~PursueAI() {};

private:

};

