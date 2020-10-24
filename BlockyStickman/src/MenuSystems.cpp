#include "MenuSystems.h"
#include "Components.h"
#include "Core.h"
#include "Entity.h"
#include "entt/entt.hpp"
#include "SFML/Graphics/View.hpp"
#include "State.h"
#include "Renderer.h"


void Blocky::MenuSystems::SelectionReportSystem(Timestep dt, entt::registry& registry, State* state)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{

		LOG("MOUSE PRESSED\n");
		sf::Vector2i mousePixels = sf::Mouse::getPosition(*Renderer::GetRenderer());
		sf::Vector2f mousePos = Renderer::GetRenderer()->mapPixelToCoords(mousePixels);
		LOG("Mouse: {} {}\n", mousePos.x, mousePos.y);

		auto textBoxes = registry.view<TextComponentPtr, FontComponentPtr>();
		for (auto entity : textBoxes)
		{
			// find position of each text box, check for any intersects with the current mouse position
			auto& textBox = registry.get<TextComponentPtr>(entity)->text;
			LOG("Box: {} {}\n", textBox.getPosition().x, textBox.getPosition().y);

			// If so, do a check to see the text of that text box and do the according action
			if (textBox.getGlobalBounds().contains(sf::Vector2f(mousePos)))
			{
				if (textBox.getString() == std::string("Start"))
				{
					// start game
					LOG("Starting Game!");
					state->requestSwap(States::Game);
				}
				else if (textBox.getString() == std::string("Exit"))
				{
					// exit game
					LOG("Exiting Game");
					state->requestStackPop();
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
