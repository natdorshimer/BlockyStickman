#include "blocky-pch.h"
#include "Core.h"
#include "MessageState.h"
#include "Components.h"
#include "LevelLoading.h"
#include "StateStack.h"
#include "GameSystems.h"
#include "Components.h"
#include "Renderer.h"
#include "LevelLoading.h"

namespace Blocky
{
	 
	void RenderMessageStateCamera(Timestep dt, entt::registry& registry)
	{
		auto entities = registry.view<TextComponentPtr, CameraComponentPtr>();

		for (auto text_entity : entities)
		{
			const auto& [text, camera] = entities.get<TextComponentPtr, CameraComponentPtr>(text_entity);

			const auto& [topLeftX, topLeftY] = text->text.getPosition();

			auto h = text->text.getGlobalBounds().height;
			auto w = text->text.getGlobalBounds().width;

			camera->view.setCenter(topLeftX+w/2,  topLeftY+h/2 );
		}
	}

	DisplayMessageState::DisplayMessageState(StateStack* parentRef, const std::string& message) 
		: State(parentRef), isStatePaused(true), scene(std::make_shared<Scene>())
	{
		//TODO: Needs a background 

		//Text with a controller so the player can unpause
		Entity text = addText(this->scene, message, "resources/stocky/stocky.ttf", 0, 0, 50, sf::Text::Style::Regular, sf::Color::White);
		LOG("Started drawing ");
		GiveComponent(text, CameraComponent);

		System RenderCam = this->scene->CreateSystem(&RenderMessageStateCamera);

		this->scene->CreateSystem([this](Timestep dt, entt::registry& registry) { this->WaitForExit(dt, registry); });

		BackgroundAnimationSystemInit();
	}


	bool DisplayMessageState::Update(Timestep dt)
	{
		this->scene->OnUpdate(dt);
		return false; //False prevents the stack from processing any states beyond this one
	}

	void DisplayMessageState::WaitForExit(Timestep dt, entt::registry& registry)
	{
		//To avoid polling repeat inputs
		static float waitTime = Input::TimeWaitForInput;

		waitTime -= dt;
		if (waitTime < 0)
		{
			//toggle the pause state upon pressing p
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				this->requestStackPop();
				waitTime = Input::TimeWaitForInput;
			}
		}
	}

	void DisplayMessageState::BackgroundAnimationSystemInit()
	{

	}
}
