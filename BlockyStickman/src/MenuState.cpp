#include "MenuState.h"
#include "Entity.h"
#include "Scene.h"
#include "Core.h"
#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "GameSystems.h"
#include "LevelLoading.h"
#include <memory>
#include "MenuSystems.h"

namespace Blocky {
	 

	MenuState::MenuState(StateStack* parentRef) :
		State(parentRef),
		scene(std::make_shared<Scene>())
	{
		// Menu Background
		Entity menu = addBackground(this->scene, "resources/Menu.png"); 

		// Start game option
		Entity start = addText(this->scene, "Start", DefaultTextPath, 13, 95, 24);

		// Exit game option
		Entity exit = addText(this->scene, "Exit", DefaultTextPath, 94, 95, 24);

		// Welcome to BlockyStickMan
		Entity titleline1 = addText(this->scene, "Welcome", DefaultTextPath, 30, 10, 20, sf::Text::Style(sf::Text::Regular), sf::Color(sf::Color::Red));
		Entity titleline2 = addText(this->scene, "to", DefaultTextPath, 70, 40, 20, sf::Text::Style(sf::Text::Regular), sf::Color(sf::Color::Blue));
		Entity titleline3 = addText(this->scene, "BlockyStickMan", DefaultTextPath, 13, 70, 15, sf::Text::Style(sf::Text::Regular), sf::Color(sf::Color::Yellow));

		// Default camera setup system
		System RenderCam = this->scene->CreateSystem(&MenuSystems::RenderCamera);

		// System for getting input/highlighting an option
		System SelectionReportSystem = this->scene->CreateSystem([this](Timestep dt, entt::registry& registry) -> void
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					LOG("MOUSE PRESSED\n");
					sf::Vector2i mousePixels = sf::Mouse::getPosition(*Renderer::GetRenderer());
					sf::Vector2f mousePos = Renderer::GetRenderer()->mapPixelToCoords(mousePixels);
					LOG("Mouse: {} {}\n", mousePos.x, mousePos.y);
					auto textBoxes = registry.view<TextComponentPtr, FontComponentPtr>();
					for (auto entity : textBoxes) {
						// find position of each text box, check for any intersects with the current mouse position
						auto& textBox = registry.get<TextComponentPtr>(entity)->text;
						LOG("Box: {} {}\n", textBox.getPosition().x, textBox.getPosition().y);
						// If so, do a check to see the text of that text box and do the according action
						if (textBox.getGlobalBounds().contains(sf::Vector2f(mousePos)))
						{
							if (textBox.getString() == std::string("Start")) {
								// start game
								LOG("Starting Game!");
								this->requestSwap(States::Game);
							}
							else if (textBox.getString() == std::string("Exit")) {
								// exit game
								LOG("Exiting Game");
								this->requestStackPop();
							}
						}
					}
				}
			}
		);
	}
		

	bool MenuState::Update(Timestep dt)
	{
		scene->OnUpdate(dt);
		return false;
	}

}