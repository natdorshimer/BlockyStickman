#pragma once

#include "blocky-pch.h"

//Since they operator on sf::Vectors this should be in the sf namespace
namespace sf
{
	std::string To_String(sf::Vector2f vec);

	float norm(sf::Vector2f v);

	sf::Vector2f operator*(sf::Vector2f first, float second);

	float dotProduct(sf::Vector2f first, sf::Vector2f second);

	sf::Vector2f getCenter(const sf::Sprite&);

	void setCenter(sf::Sprite&, const sf::Vector2f&);
}
