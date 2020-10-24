#include "VectorMath.h"

std::string sf::To_String(sf::Vector2f vec)
{
	return std::to_string(vec.x) + ", " + std::to_string(vec.y);
}

float sf::norm(sf::Vector2f v)
{
	return sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
}

float sf::dotProduct(sf::Vector2f first, sf::Vector2f second)
{
	return first.x * second.x + first.y * second.y;
}

//Scalar multiplication 
namespace sf
{
	sf::Vector2f operator*(sf::Vector2f first, float second)
	{
		sf::Vector2f result;
		result.x = first.x * second;
		result.y = first.y * second;

		return result;
	}
}

// Sprite center getter/setters
namespace sf
{

	sf::Vector2f getCenter(const sf::Sprite& sprite)
	{
		auto [topLeftX, topLeftY] = sprite.getPosition();
		
		float width = sprite.getGlobalBounds().width;
		float height = sprite.getGlobalBounds().height;
		return  sf::Vector2f(topLeftX + width / 2.0, topLeftY + height / 2.0);
	}

	void setCenter(sf::Sprite& sprite, const sf::Vector2f& v)
	{
		float center_x = v.x;
		float center_y = v.y;

		
		float sprite_width = sprite.getGlobalBounds().width;
		float sprite_height = sprite.getGlobalBounds().height;

		sprite.setPosition(sf::Vector2f(v.x - sprite_width / 2.0, v.y - sprite_height / 2.0));
	}

}