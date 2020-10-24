#include "MenuSystems.h"
#include "Components.h"
#include "Core.h"
#include "Entity.h"
#include "entt/entt.hpp"
#include "SFML/Graphics/View.hpp"


void Blocky::MenuSystems::SelectionReportSystem(Timestep dt, entt::registry& registry)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		auto textBoxes = registry.view<TextComponentPtr, FontComponentPtr>();
		// TODO find position of each text box, and see if the position of any intersects/contains the current mouse position. 
		for (auto entity : textBoxes) {
			// If so, do a check to see the text of that text box and do the according action
			auto& textBox = registry.get<TextComponentPtr>(entity)->text;
			if (textBox.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				if (textBox.getString() == "Start") {
					// start game
				}
				else if (textBox.getString() == "Exit") {
					// exit game
				}
			}
		}
	}
}

// centers all cameras in the right places
void Blocky::MenuSystems::RenderCamera(Timestep dt, entt::registry& registry)
{
	auto entities = registry.view<SpriteComponentPtr, CameraComponentPtr>();

	for (auto sprite_entity : entities)
	{
		auto& [sprite, camera] = entities.get<SpriteComponentPtr, CameraComponentPtr>(sprite_entity);

		auto& [topLeftX, topLeftY] = sprite->sprite.getPosition();
		auto h = sprite->sprite.getGlobalBounds().height;
		auto w = sprite->sprite.getGlobalBounds().width;

		camera->view.setCenter(topLeftX + w/2, topLeftY + h/2);
	}
	
}
