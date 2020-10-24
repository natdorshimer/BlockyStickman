#include "blocky-pch.h"
#include "GameState.h"
#include "Scene.h"
#include "Core.h"
#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "GameSystems.h"
#include "LevelLoading.h"


namespace Blocky
{
	std::shared_ptr<Scene>& GameState::GetScene()
	{
		return m_Scene;
	}

	GameState::GameState(StateStack* parentStack) :
		State(parentStack),
		m_Scene(std::make_shared<Scene>()),
		m_IsStatePaused(false), 
		m_shouldContinue(true)
	{
		EntityComponentInit();

		SystemInit();

		InitWinConditionSystems();
	}



	void GameState::EntityComponentInit()
	{

		 
		//The world can have various properties, e.g. gravity
		Entity world = m_Scene->CreateEntity();
		GiveComponent(world, WorldStateComponent);


		//This is the character that we control
		std::string blockyFilepath = "resources/blocky32.png";
		Entity playerCharacter = addPlayer(m_Scene, blockyFilepath, 225, 100);


		std::string enemyFilepath = "resources/enemy32.png";

		//Creates two enemies in the scene. Blocky dies if he touches them anywhere other than their heads
		Entity enemy = addStaticSprite(m_Scene, enemyFilepath);
		GiveComponent(enemy, ColliderComponent);
		enemyColliderComponent->priority = ColliderComponent::Highest;


		Entity enemy2 = addStaticSprite(m_Scene, enemyFilepath, 25, 25);
		GiveComponent(enemy2, ColliderComponent);
		enemy2ColliderComponent->priority = ColliderComponent::Highest;


		//You win if you touch this block!
		Entity winBlock = addStaticSprite(m_Scene, enemyFilepath, -100, -100);
		GiveComponent(winBlock, ColliderComponent);
		GiveComponent(winBlock, WinConditionComponent);
		winBlockColliderComponent->priority = ColliderComponent::Highest;

		Entity testBoxWin = addText(m_Scene, "Congrats on finding this :)", DefaultTextPath, -150, -200);


		//Creates an enemy in the scene
		Entity enemyMover = addEnemy(m_Scene, enemyFilepath, 60, -60);

		/********************* Level Blocks **************************************************************/
		std::string groundFilePath = "resources/GroundAndStone/GroundAndStone/Ground/ground5.png";
		std::string stoneFilePath = "resources/GroundAndStone/GroundAndStone/Stone/ground5.png";

		// Left wall
		Entity lwb1 = addStaticSprite(m_Scene, groundFilePath, 0, 64, 0.5, 0.5);
		GiveComponent(lwb1, ColliderComponent);
		lwb1ColliderComponent->priority = ColliderComponent::Highest;
		Entity lwb2 = addStaticSprite(m_Scene, groundFilePath, 0, 128, 0.5, 0.5);
		GiveComponent(lwb2, ColliderComponent);
		lwb2ColliderComponent->priority = ColliderComponent::Highest;
		Entity lwb3 = addStaticSprite(m_Scene, groundFilePath, 0, 192, 0.5, 0.5);
		GiveComponent(lwb3, ColliderComponent);
		lwb3ColliderComponent->priority = ColliderComponent::Highest;
		Entity lwb4 = addStaticSprite(m_Scene, groundFilePath, 0, 256, 0.5, 0.5);
		GiveComponent(lwb4, ColliderComponent);
		lwb4ColliderComponent->priority = ColliderComponent::Highest;

		// start of ground
		Entity g1b1 = addStaticSprite(m_Scene, groundFilePath, 64, 256, 0.5, 0.5);
		GiveComponent(g1b1, ColliderComponent);
		g1b1ColliderComponent->priority = ColliderComponent::Highest;
		Entity g1b2 = addStaticSprite(m_Scene, groundFilePath, 128, 256, 0.5, 0.5);
		GiveComponent(g1b2, ColliderComponent);
		g1b2ColliderComponent->priority = ColliderComponent::Highest;
		Entity g1b3 = addStaticSprite(m_Scene, groundFilePath, 192, 256, 0.5, 0.5);
		GiveComponent(g1b3, ColliderComponent);
		g1b3ColliderComponent->priority = ColliderComponent::Highest;
		Entity g1b4 = addStaticSprite(m_Scene, groundFilePath, 256, 256, 0.5, 0.5);
		GiveComponent(g1b4, ColliderComponent);
		g1b4ColliderComponent->priority = ColliderComponent::Highest;
		Entity g1b5 = addStaticSprite(m_Scene, groundFilePath, 320, 256, 0.5, 0.5);
		GiveComponent(g1b5, ColliderComponent);
		g1b5ColliderComponent->priority = ColliderComponent::Highest;

		// small hole with enemy in it
		Entity g2b1 = addStaticSprite(m_Scene, groundFilePath, 384, 288, 0.5, 0.5);
		GiveComponent(g2b1, ColliderComponent);
		g2b1ColliderComponent->priority = ColliderComponent::Highest;
		Entity g2b2 = addStaticSprite(m_Scene, groundFilePath, 448, 288, 0.5, 0.5);
		GiveComponent(g2b2, ColliderComponent);
		g2b2ColliderComponent->priority = ColliderComponent::Highest;
		Entity g2b3 = addStaticSprite(m_Scene, groundFilePath, 512, 288, 0.5, 0.5);
		GiveComponent(g2b3, ColliderComponent);
		g2b3ColliderComponent->priority = ColliderComponent::Highest;
		Entity e1 = addEnemy(m_Scene, enemyFilepath, 450, 228);

		// platforms above hole
		Entity p1b1 = addStaticSprite(m_Scene, groundFilePath, 384, 193, 0.15, 0.15);
		GiveComponent(p1b1, ColliderComponent);
		p1b1ColliderComponent->priority = ColliderComponent::Highest;
		Entity p1b2 = addStaticSprite(m_Scene, groundFilePath, 448, 193, 0.15, 0.15);
		GiveComponent(p1b2, ColliderComponent);
		p1b2ColliderComponent->priority = ColliderComponent::Highest;
		Entity p1b3 = addStaticSprite(m_Scene, groundFilePath, 512, 193, 0.15, 0.15);
		GiveComponent(p1b3, ColliderComponent);
		p1b3ColliderComponent->priority = ColliderComponent::Highest;

		// 2nd long ground leading to stairs
		Entity g3b1 = addStaticSprite(m_Scene, groundFilePath, 576, 256, 0.5, 0.5);
		GiveComponent(g3b1, ColliderComponent);
		g3b1ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b2 = addStaticSprite(m_Scene, groundFilePath, 640, 256, 0.5, 0.5);
		GiveComponent(g3b2, ColliderComponent);
		g3b2ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b3 = addStaticSprite(m_Scene, groundFilePath, 704, 256, 0.5, 0.5);
		GiveComponent(g3b3, ColliderComponent);
		g3b3ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b4 = addStaticSprite(m_Scene, groundFilePath, 768, 256, 0.5, 0.5);
		GiveComponent(g3b4, ColliderComponent);
		g3b4ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b5 = addStaticSprite(m_Scene, groundFilePath, 832, 256, 0.5, 0.5);
		GiveComponent(g3b5, ColliderComponent);
		g3b5ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b6 = addStaticSprite(m_Scene, groundFilePath, 896, 256, 0.5, 0.5);
		GiveComponent(g3b6, ColliderComponent);
		g3b6ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b7 = addStaticSprite(m_Scene, groundFilePath, 960, 256, 0.5, 0.5);
		GiveComponent(g3b7, ColliderComponent);
		g3b7ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b8 = addStaticSprite(m_Scene, groundFilePath, 1024, 256, 0.5, 0.5);
		GiveComponent(g3b8, ColliderComponent);
		g3b8ColliderComponent->priority = ColliderComponent::Highest;
		Entity g3b9 = addStaticSprite(m_Scene, groundFilePath, 1024, 192, 0.5, 0.5);
		GiveComponent(g3b9, ColliderComponent);
		g3b9ColliderComponent->priority = ColliderComponent::Highest;

		// plats above 2nd long ground, w/3 enemies
		Entity p2b1 = addStaticSprite(m_Scene, stoneFilePath, 615, 161, 0.125, 0.125);
		GiveComponent(p2b1, ColliderComponent);
		p2b1ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b2 = addStaticSprite(m_Scene, stoneFilePath, 631, 161, 0.125, 0.125);
		GiveComponent(p2b2, ColliderComponent);
		p2b2ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b3 = addStaticSprite(m_Scene, stoneFilePath, 647, 161, 0.125, 0.125);
		GiveComponent(p2b3, ColliderComponent);
		p2b3ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b7 = addStaticSprite(m_Scene, stoneFilePath, 663, 161, 0.125, 0.125);
		GiveComponent(p2b7, ColliderComponent);
		p2b7ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b8 = addStaticSprite(m_Scene, stoneFilePath, 679, 161, 0.125, 0.125);
		GiveComponent(p2b8, ColliderComponent);
		p2b8ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b9 = addStaticSprite(m_Scene, stoneFilePath, 695, 161, 0.125, 0.125);
		GiveComponent(p2b9, ColliderComponent);
		p2b9ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b10 = addStaticSprite(m_Scene, stoneFilePath, 711, 161, 0.125, 0.125);
		GiveComponent(p2b10, ColliderComponent);
		p2b10ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b11 = addStaticSprite(m_Scene, stoneFilePath, 726, 161, 0.125, 0.125);
		GiveComponent(p2b11, ColliderComponent);
		p2b11ColliderComponent->priority = ColliderComponent::Highest;

		Entity e2 = addEnemy(m_Scene, enemyFilepath, 684, 200);

		Entity p2b4 = addStaticSprite(m_Scene, stoneFilePath, 844, 161, 0.125, 0.125);
		GiveComponent(p2b4, ColliderComponent);
		p2b4ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b5 = addStaticSprite(m_Scene, stoneFilePath, 860, 161, 0.125, 0.125);
		GiveComponent(p2b5, ColliderComponent);
		p2b5ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b6 = addStaticSprite(m_Scene, stoneFilePath, 866, 161, 0.125, 0.125);
		GiveComponent(p2b6, ColliderComponent);
		p2b6ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b12 = addStaticSprite(m_Scene, stoneFilePath, 882, 161, 0.125, 0.125);
		GiveComponent(p2b12, ColliderComponent);
		p2b12ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b13 = addStaticSprite(m_Scene, stoneFilePath, 898, 161, 0.125, 0.125);
		GiveComponent(p2b13, ColliderComponent);
		p2b13ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b14 = addStaticSprite(m_Scene, stoneFilePath, 914, 161, 0.125, 0.125);
		GiveComponent(p2b14, ColliderComponent);
		p2b14ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b15 = addStaticSprite(m_Scene, stoneFilePath, 930, 161, 0.125, 0.125);
		GiveComponent(p2b15, ColliderComponent);
		p2b15ColliderComponent->priority = ColliderComponent::Highest;
		Entity p2b16 = addStaticSprite(m_Scene, stoneFilePath, 946, 161, 0.125, 0.125);
		GiveComponent(p2b16, ColliderComponent);
		p2b16ColliderComponent->priority = ColliderComponent::Highest;

		Entity e3 = addEnemy(m_Scene, enemyFilepath, 890, 200);
		Entity e4 = addEnemy(m_Scene, enemyFilepath, 980, 200);

		// stairs
		Entity s1b1 = addStaticSprite(m_Scene, groundFilePath, 1088, 192, 0.5, 0.5);
		GiveComponent(s1b1, ColliderComponent);
		s1b1ColliderComponent->priority = ColliderComponent::Highest;
		Entity s1b2 = addStaticSprite(m_Scene, groundFilePath, 1088, 128, 0.5, 0.5);
		GiveComponent(s1b2, ColliderComponent);
		s1b2ColliderComponent->priority = ColliderComponent::Highest;
		Entity s1b3 = addStaticSprite(m_Scene, groundFilePath, 1152, 128, 0.5, 0.5);
		GiveComponent(s1b3, ColliderComponent);
		s1b3ColliderComponent->priority = ColliderComponent::Highest;
		Entity s1b4 = addStaticSprite(m_Scene, groundFilePath, 1152, 64, 0.5, 0.5);
		GiveComponent(s1b4, ColliderComponent);
		s1b4ColliderComponent->priority = ColliderComponent::Highest;


		// Final ground to end goal
		Entity g4b1 = addStaticSprite(m_Scene, stoneFilePath, 1216, 64, 0.5, 0.5);
		GiveComponent(g4b1, ColliderComponent);
		g4b1ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b1sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b1.GetID())->sprite;
		g4b1sprite.setColor(sf::Color(128, 0, 0)); //maroon

		Entity g4b2 = addStaticSprite(m_Scene, stoneFilePath, 1280, 64, 0.5, 0.5);
		GiveComponent(g4b2, ColliderComponent);
		g4b2ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b2sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b2.GetID())->sprite;
		g4b2sprite.setColor(sf::Color::Red);

		Entity g4b3 = addStaticSprite(m_Scene, stoneFilePath, 1344, 64, 0.5, 0.5);
		GiveComponent(g4b3, ColliderComponent);
		g4b3ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b3sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b3.GetID())->sprite;
		g4b3sprite.setColor(sf::Color(255, 165, 0)); //orange

		Entity g4b4 = addStaticSprite(m_Scene, stoneFilePath, 1408, 64, 0.5, 0.5);
		GiveComponent(g4b4, ColliderComponent);
		g4b4ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b4sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b4.GetID())->sprite;
		g4b4sprite.setColor(sf::Color::Yellow);

		Entity g4b5 = addStaticSprite(m_Scene, stoneFilePath, 1472, 64, 0.5, 0.5);
		GiveComponent(g4b5, ColliderComponent);
		g4b5ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b5sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b5.GetID())->sprite;
		g4b5sprite.setColor(sf::Color::Green);

		Entity g4b6 = addStaticSprite(m_Scene, stoneFilePath, 1536, 64, 0.5, 0.5);
		GiveComponent(g4b6, ColliderComponent);
		g4b6ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b6sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b6.GetID())->sprite;
		g4b6sprite.setColor(sf::Color::Blue);

		Entity g4b7 = addStaticSprite(m_Scene, stoneFilePath, 1600, 64, 0.5, 0.5);
		GiveComponent(g4b7, ColliderComponent);
		g4b7ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b7sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b7.GetID())->sprite;
		g4b7sprite.setColor(sf::Color(75, 0, 130)); // indigo

		Entity g4b8 = addStaticSprite(m_Scene, stoneFilePath, 1664, 64, 0.5, 0.5);
		GiveComponent(g4b8, ColliderComponent);
		g4b8ColliderComponent->priority = ColliderComponent::Highest;
		auto& g4b8sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(g4b8.GetID())->sprite;
		g4b8sprite.setColor(sf::Color(128, 0, 128)); //violet

		// Win 
		Entity winBlock2 = addStaticSprite(m_Scene, stoneFilePath, 1728, 64, 0.5, 0.5);
		GiveComponent(winBlock2, ColliderComponent);
		GiveComponent(winBlock2, WinConditionComponent);
		winBlock2ColliderComponent->priority = ColliderComponent::Highest;
		auto& winb2Sprite = m_Scene->GetRegistry().get<SpriteComponentPtr>(winBlock2.GetID())->sprite;
		winb2Sprite.setColor(sf::Color::White);
		// Flag 
		Entity flag = addStaticSprite(m_Scene, "resources/redflagtransparentbg.png", 1750, 4);
		GiveComponent(flag, ColliderComponent);
		GiveComponent(flag, WinConditionComponent);
		flagColliderComponent->priority = ColliderComponent::Highest;

		// Final enemies
		Entity e6 = addEnemy(m_Scene, enemyFilepath, 1280, 0);
		Entity e7 = addEnemy(m_Scene, enemyFilepath, 1408, 0);
		Entity e8 = addEnemy(m_Scene, enemyFilepath, 1536, 0);
		Entity e9 = addEnemy(m_Scene, enemyFilepath, 1600, 0);
		
		// Timer that follows Player around
		Entity timer = addText(m_Scene, "0", DefaultTextPath, 0, 0);
		GiveComponent(timer, TimerComponent);

		// Level Background
		Entity bg = addBackground(m_Scene, "resources/country-platform-files/country-platform-files/country-platform-preview.png");

	}

	void GameState::SystemInit()
	{
		//Systems describe the behavior of the scene. Register them and let em do their thing, that's a scene!
		//System operate in reverse order


		//Render logic
		this->m_Scene->CreateSystem(&GameSystems::RenderCamera);


		//End of frame logic
		this->m_Scene->CreateSystem(&GameSystems::ClearCollisionNormals);
		this->m_Scene->CreateSystem(&GameSystems::UpdateObjectState);


		//Damage / Combat
		this->m_Scene->CreateSystem(&GameSystems::EnemyDamageSystem);
		this->m_Scene->CreateSystem(&GameSystems::PlayerDamageSystem);


		//The computer controls the enemies
		this->m_Scene->CreateSystem(&GameSystems::AIControllerSystemBasic);


		//Movement
		this->m_Scene->CreateSystem(&GameSystems::TranslationSystem);
		this->m_Scene->CreateSystem(&GameSystems::GravitySystem);
		this->m_Scene->CreateSystem(&GameSystems::MovementControllerSystem);
		this->m_Scene->CreateSystem(&GameSystems::ColliderSystem);


		//Load scene logic
		this->m_Scene->CreateSystem(&GameSystems::TimerDisplaySystem);
		this->m_Scene->CreateSystem(&GameSystems::CenterBackgroundOnPlayerSystem);

		
		//Debug tools
		this->m_Scene->CreateSystem(&GameSystems::PlayerCharacterLogger);


		//This legitimately worked the first time lol
		auto spawnSystem = [this](Timestep dt, entt::registry& registry)
		{
			GameSystems::SpawnEnemiesUponTimerMax(dt, registry, this->GetScene());
		};

		this->m_Scene->CreateSystem(spawnSystem);

	}

	//These systems actually rely upon the current scene instance, and don't just act upon the registry
	//That's because these actually need to call a state-switch upon certain conditions
	void GameState::InitWinConditionSystems()
	{
		auto checkPlayerDeath = [this](Timestep dt, entt::registry& registry)
		{ 
			this->CheckGameOverCondition(dt, registry); 
		};

		auto pauseChecker = [this](Timestep dt, entt::registry& registry) 
		{ 
			this->PauseChecker(dt, registry); 
		};

		auto winCondition = [this](Timestep dt, entt::registry& registry)
		{
			this->WinConditionSystem(dt, registry);
		};

		this->m_Scene->CreateSystem(pauseChecker);
		this->m_Scene->CreateSystem(checkPlayerDeath);
		this->m_Scene->CreateSystem(winCondition);
	}

	void GameState::BlockNextState()
	{
		m_shouldContinue = false;
	}

	void GameState::AllowNextState()
	{
		m_shouldContinue = true;
	}

	bool GameState::ShouldContinue()
	{
		return m_shouldContinue;
	}


	void GameState::WinConditionSystem(Timestep dt, entt::registry& registry)
	{
		auto playerView = registry.view<PlayerCharacterGroup>();
		auto player_ent = playerView.front();
		auto& player_collider = playerView.get<ColliderComponentPtr>(player_ent);

		auto win_collider_ents = registry.view<WinConditionComponentPtr>();

		for (auto win_collider_ent : win_collider_ents)
		{
			if (player_collider->normals.count(win_collider_ent) > 0)
			{
				this->requestSwap(States::GameWon);
				m_shouldContinue = false;
				break;
			}
		}
	}

	void GameState::CheckGameOverCondition(Timestep dt, entt::registry& registry)
	{
		auto view = registry.view<PlayerCharacterGroup>();

		auto& status = view.get<StatusComponentPtr>(view.front());

		//GAME OVER STATE
		if (status->Health <= 0)
		{
			OnGameOver(dt);
		}
	}

	//TODO: get better ways to handle input polling 
	void GameState::PauseChecker(Timestep dt, entt::registry& registry)
	{
		//To avoid polling repeat inputs
		static float waitTime = Input::TimeWaitForInput;

		waitTime -= dt;
		if (waitTime < 0)
		{
			//toggle the pause state upon pressing p
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				this->requestStackPush(States::Pause); //TODO: Implement the pause state pop

				BlockNextState(); //Prevents the layer stack from progressing to the next state

				waitTime = Input::TimeWaitForInput;
			}
		}
	};

	//Swaps to game over state
	void GameState::OnGameOver(Timestep dt)
	{
		this->requestSwap(States::GameOver);

		BlockNextState();
	}

	bool Blocky::GameState::Update(Timestep dt)
	{
		//Allow the next state unless the update says otherwise
		AllowNextState();

		m_Scene->OnUpdate(dt);

		//If it returns false, it should not continue to the next scene
		return ShouldContinue();
	}

}