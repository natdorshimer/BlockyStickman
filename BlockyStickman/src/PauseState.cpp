#include "Core.h"
#include "PauseState.h"
#include "Components.h"
#include "LevelLoading.h"
#include "StateStack.h"
#include <entt/entt.hpp>
#include "Renderer.h"
#include "GameSystems.h"


namespace Blocky
{


	void RenderPauseStateCamera(Timestep dt, entt::registry& registry)
	{
		auto entities = registry.view<TextComponentPtr, CameraComponentPtr>();

		for (auto text_entity : entities)
		{
			auto& [text, camera] = entities.get<TextComponentPtr, CameraComponentPtr>(text_entity);

			auto& [topLeftX, topLeftY] = text->text.getPosition();

			auto h = text->text.getGlobalBounds().height;
			auto w = text->text.getGlobalBounds().width;

			camera->view.setCenter(topLeftX + w / 2, topLeftY + h / 2);
		}
	}

	PauseState::PauseState(StateStack* parentRef) : State(parentRef), isStatePaused(true), scene(std::make_shared<Scene>())
	{
		//TODO: Needs a background 

		//Text with a controller so the player can unpause
		Entity text = addText(this->scene, "Paused", "resources/stocky/stocky.ttf", 0, 0, 50, sf::Text::Style::Regular, sf::Color::White);
		LOG("Started drawing ");
		GiveComponent(text, CameraComponent);

		System RenderCam = this->scene->CreateSystem(&RenderPauseStateCamera);

		this->scene->CreateSystem([this](Timestep dt, entt::registry& registry) { this->PauseChecker(dt, registry); });

		BackgroundAnimationSystemInit();
	}

	void PauseState::PauseChecker(Timestep dt, entt::registry& registry)
	{
		//To avoid polling repeat inputs
		static float waitTime = Input::TimeWaitForInput;

		waitTime -= dt;
		if (waitTime < 0)
		{
			//toggle the pause state upon pressing p
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				LOG("Removing Pause State From Front\n");
				this->requestStackPop();
				waitTime = Input::TimeWaitForInput;
			}
		}
	};

	bool PauseState::Update(Timestep dt)
	{
		this->scene->OnUpdate(dt);
		return false; //False prevents the stack from processing any states beyond this one
	}

	void PauseState::BackgroundAnimationSystemInit()
	{
		std::string blockyFilepath = "resources/blocky32.png";

		Entity world = scene->CreateEntity();
		GiveComponent(world, WorldStateComponent);

		int windowX = Renderer::GetRenderer()->getView().getSize().x;
		int windowY = Renderer::GetRenderer()->getView().getSize().y;

		float yStart = -(float)(windowY);

		Entity blocky1 = addStaticSprite(scene, blockyFilepath, (float)(rand() % windowX), -yStart);
		GiveComponent(blocky1, VelocityComponent);
		GiveComponent(blocky1, RotationComponent);
		GiveComponent(blocky1, ObjectState);
		blocky1VelocityComponent->velocity.y = (float)(rand() % 1000);

		Entity blocky2 = addStaticSprite(scene, blockyFilepath, (float)(rand() % windowX), yStart);
		GiveComponent(blocky2, VelocityComponent);
		GiveComponent(blocky2, RotationComponent);
		GiveComponent(blocky2, ObjectState);
		blocky2VelocityComponent->velocity.y = (float)(rand() % 1000);

		Entity blocky3 = addStaticSprite(scene, blockyFilepath, (float)(rand() % windowX), yStart);
		GiveComponent(blocky3, VelocityComponent);
		GiveComponent(blocky3, RotationComponent);
		GiveComponent(blocky3, ObjectState);
		blocky3VelocityComponent->velocity.y = (float)(rand() % 1000);

		Entity blocky4 = addStaticSprite(scene, blockyFilepath, (float)(rand() % windowX), yStart);
		GiveComponent(blocky4, VelocityComponent);
		GiveComponent(blocky4, RotationComponent);
		GiveComponent(blocky4, ObjectState);
		blocky4VelocityComponent->velocity.y = (float)(rand() % 1000);

		Entity blocky5 = addStaticSprite(scene, blockyFilepath, (float)(rand() % windowX), yStart);
		GiveComponent(blocky5, VelocityComponent);
		GiveComponent(blocky5, RotationComponent);
		GiveComponent(blocky5, ObjectState);
		blocky5VelocityComponent->velocity.y = (float)(rand() % 1000);

		Entity blocky6 = addStaticSprite(scene, blockyFilepath, (float)(rand() % windowX), yStart);
		GiveComponent(blocky6, VelocityComponent);
		GiveComponent(blocky6, RotationComponent);
		GiveComponent(blocky6, ObjectState);
		blocky6VelocityComponent->velocity.y = (float)(rand() % 1000);



		this->scene->CreateSystem(&GameSystems::TranslationSystem);
		this->scene->CreateSystem(&GameSystems::GravitySystem);

		this->scene->CreateSystem(&GameSystems::ConstantRotationSystem);
		this->scene->CreateSystem(&GameSystems::PositionResetSystemForPauseState);
	}

}
