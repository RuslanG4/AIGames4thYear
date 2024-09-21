#pragma once
#include<SFML/Graphics.hpp>
#include<functional>
#include<iostream>

#include"Utility.h"
#include "Constants.h"
#include"VisionCone.h"
#include<random>

class AI
{
public:
	AI(sf::Vector2f position, const sf::Texture & texture);
	virtual void update(double dt);
	void render(sf::RenderWindow& window);

protected:
	sf::Vector2f getAheadVector() const { return m_ahead; };
	sf::Sprite getSprite() const { return body; };
	void setPosition(sf::Vector2f pos)
	{
		body.setPosition(pos);
	}
	void setRotation(float angle)
	{
		float temp = angle - 90;
		if(m_rotation < temp)
		{
			m_rotation++;
		}
		else if(m_rotation>temp)
		{
			m_rotation--;
		}
		if (m_rotation == temp)
		{
			
		}
		body.setRotation(m_rotation);
	}
	float getRotation() { return m_rotation - 90; };

private:
	VisionCone* visionCone;
	sf::Texture bodyTexture;
	sf::Sprite body;

	sf::VertexArray m_points;
	sf::Vertex m_start;

	// The ahead vector.
	sf::Vector2f m_ahead;

	float m_rotation{0.0};

	void calculateAheadVector();
	void points();
	void boundary();
};

