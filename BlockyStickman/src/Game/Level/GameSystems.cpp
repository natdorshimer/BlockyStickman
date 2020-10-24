#include "blocky-pch.h"
#include "GameSystems.h"
#include "Components.h"
#include "Core.h"
#include "VectorMath.h"
#include "Renderer.h"
#include "Entity.h"
#include "LevelLoading.h"

namespace Blocky
{
	 

	static bool isColliding(SpriteComponentPtr s1, SpriteComponentPtr s2)
	{
		return s1->sprite.getGlobalBounds().intersects(s2->sprite.getGlobalBounds());
	}

	//Returns true if the normal is facing upwards at more than 45 degrees
	static bool hasNormalUpward(const std::map<entt::entity, sf::Vector2f>& normals)
	{
		auto isUpward = [](std::pair<entt::entity, sf::Vector2f> p) { return p.second.y > 0; };
		auto location = std::find_if(normals.begin(), normals.end(), isUpward);

		return location != normals.end() && (abs(location->second.y) > abs(location->second.x));
	}


	void GameSystems::RenderCamera(Timestep dt, entt::registry& registry)
	{
		auto camera_view = registry.view<SpriteComponentPtr, PlayerControllerPtr, CameraComponentPtr>();
		auto camera_entity = camera_view.front();

		auto& [sprite, camera] = camera_view.get<SpriteComponentPtr, CameraComponentPtr>(camera_entity);

		//camera->view.setCenter(sprite->sprite.getPosition());
		camera->view.setCenter(sf::getCenter(sprite->sprite));


	}

	void GameSystems::GravitySystem(Timestep dt, entt::registry& registry)
	{
		auto view = registry.group<VelocityComponentPtr, ObjectStatePtr>();

		auto worldviews = registry.view<WorldStateComponentPtr>();

		auto& worldstate = registry.get<WorldStateComponentPtr>(worldviews.front());



		for (auto ent : view)
		{
			bool isAirborne = view.get<ObjectStatePtr>(ent)->HasState(ObjectState::ObjStates::Airborne);
			if (isAirborne)
			{
				auto& velocity = view.get<VelocityComponentPtr>(ent);

				velocity->velocity.y += worldstate->gravity * dt;
			}
		}
	}

	//Updates velocity and position of all entities that have velocity and sprite components
	void GameSystems::TranslationSystem(Timestep dt, entt::registry& registry)
	{
		auto view = registry.view<SpriteComponentPtr, VelocityComponentPtr>();

		for (auto ent : view)
		{
			auto& [sprite, velocity] = view.get<SpriteComponentPtr, VelocityComponentPtr>(ent);

			auto dx = velocity->velocity.x * dt; // dx/dt * dt = dx
			auto dy = velocity->velocity.y * dt;

			sprite->sprite.move(dx, dy);
		}
	}


	void GameSystems::PlayerCharacterLogger(Timestep dt, entt::registry& registry)
	{
		#ifdef BLKY_DEBUG

		auto view = registry.view<PlayerCharacterGroup>();
		auto playerEntity = view.front();

		auto& sprite = view.get<SpriteComponentPtr>(playerEntity);
		auto& velocity = view.get<VelocityComponentPtr>(playerEntity);
		auto& collider = view.get<ColliderComponentPtr>(playerEntity);
		auto& status = view.get<StatusComponentPtr>(playerEntity);
		auto& objState = view.get<ObjectStatePtr>(playerEntity);

		LOG("Begin PlayerCharacter Status: \n");
		LOG("Position: {}, {}\n", sprite->sprite.getPosition().x, sprite->sprite.getPosition().y);
		LOG("Velocity: {}, {}\n", velocity->velocity.x, velocity->velocity.y);
		LOG("ObjectState: {}\n", objState->To_String());
		LOG("Health: {}\n", status->Health);
		LOG("ColliderState: hasNormals: {}, \n", collider->hasNormals());
		std::for_each(collider->normals.begin(), collider->normals.end(),
			[](std::pair<const entt::entity, sf::Vector2f> norm)
			{
				LOG("ID: {},   Normal: {} \n", norm.first, sf::To_String(norm.second));
			}
		);
		LOG("\n\n");

		#endif
	}


	//TODO: Extremely messy and non-optimized
	void GameSystems::MovementControllerSystem(Timestep dt, entt::registry& registry)
	{
		auto view = registry.view<MovementControllerGroup>();

		for (auto ent : view)
		{
			auto& [controller, sprite, velocity, status, states, collider] = view.get<MovementControllerGroup>(ent);

			using OState = ObjectState::ObjStates;

			//Reset every frame to receive input
			velocity->velocity.x = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					velocity->velocity.x = -status->Speed;

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					velocity->velocity.x = status->Speed;

				if (!states->HasState(OState::Airborne))
				{
					states->SetState(ObjectState::ObjStates::Walking);
					velocity->velocity.y = 0;
				}
			}

			//Jumps!
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !states->HasState(OState::Airborne))
			{
				velocity->velocity += sf::Vector2f(0, status->JumpSpeed);

				states->SetState(ObjectState::Airborne);
			}

			if (!states->HasState(OState::Airborne))
			{
				velocity->velocity.y = 0;
				states->SetState(ObjectState::ObjStates::Walking);
			}

		}
	}


	void GameSystems::UpdateObjectState(Timestep dt, entt::registry& registry)
	{
		auto view = registry.view<ObjectStatePtr, VelocityComponentPtr, ColliderComponentPtr>();

		for (auto ent : view)
		{
			auto& [s, vel, col] = view.get<ObjectStatePtr, VelocityComponentPtr, ColliderComponentPtr>(ent);
			if (s->HasState(ObjectState::Airborne) && hasNormalUpward(col->normals))
			{
				s->RemoveState(ObjectState::Airborne);
				s->SetState(ObjectState::Walking);
				vel->velocity.y = 0;
			}
			else if (!hasNormalUpward(col->normals))
			{
				s->SetState(ObjectState::Airborne);
			}
		}
	}


	void GameSystems::AIControllerSystemBasic(Timestep dt, entt::registry& registry)
	{

		auto view = registry.view<AIControllerGroup>();
		for (auto ent : view)
		{
			auto& spritePtr = view.get<SpriteComponentPtr>(ent);
			auto& velPtr = view.get<VelocityComponentPtr>(ent);
			auto& statePtr = view.get<ObjectStatePtr>(ent);
			auto& controlPtr = view.get<AIControllerPtr>(ent);

			if (controlPtr->timeUntilReverse < 0)
			{
				controlPtr->speed *= -1;
				controlPtr->resetTime();
			}
			controlPtr->timeUntilReverse -= dt;

			velPtr->velocity.x = controlPtr->speed;
		}
	}

	void GameSystems::PlayerDamageSystem(Timestep dt, entt::registry& registry)
	{
		auto view = registry.view<PlayerDamageGroup>();

		for (auto ent : view)
		{
			auto& playerStatus = view.get<StatusComponentPtr>(ent);
			auto& collider = view.get<ColliderComponentPtr>(ent);

			//Blocky only takes damage if he has non-upward normals 
			//AKA, blocky takes damage when he's not jumping on enemies
			for (auto& normals : collider->normals)
			{
				auto other_ent = normals.first;
				auto& normal = normals.second;

				//If the thing it has a normal to is an enemy
				if (registry.has<AIControllerPtr>(other_ent))
				{
					auto& other_ent_status = registry.get<StatusComponentPtr>(other_ent);
					if(abs(normal.y) < abs(normal.x) && normal.y < 0)
						playerStatus->Health -= other_ent_status->AttackPower;

					//TODO add invulnerability checks
				}
			}
		}
	}



	//Helper methods 


	//Goes back in time to revert any movement that caused a collision 
	//Direction is a unit vector
	static void revertPosition(SpriteComponentPtr sprite, VelocityComponentPtr vel, sf::Vector2f direction, Timestep dt)
	{
		auto speed = sf::dotProduct(vel->velocity, direction);

		auto moveAmount = -(direction * dt);

		sprite->sprite.move(moveAmount);
	}


	//Gets the normal of s1 to s2


	static sf::Vector2f getNormal(SpriteComponentPtr s1, SpriteComponentPtr s2)
	{
		sf::Vector2f direction = sf::getCenter(s2->sprite) - sf::getCenter(s1->sprite);
		
		return direction / sf::norm(direction);
	}


	//Clears normals if they're not colliding. Meant to be done at the end of every frame. 
	void GameSystems::ClearCollisionNormals(Timestep dt, entt::registry& registry)
	{
		//Everything with a position and a collider needs to be considered
		auto collidables = registry.view<SpriteComponentPtr, ColliderComponentPtr>();

		auto moveables = registry.view<SpriteComponentPtr, ColliderComponentPtr, VelocityComponentPtr>();
		for (entt::entity mover : moveables)
		{
			//Get grouping for the moving entity
			auto& [move_sprite, move_collider, move_velocity] = moveables.get<SpriteComponentPtr, ColliderComponentPtr, VelocityComponentPtr>(mover);

			for (entt::entity other_ent : collidables)
			{
				//Get grouping for the entity the mover is colliding with
				auto& [c_sprite, c_collider] = collidables.get<SpriteComponentPtr, ColliderComponentPtr>(other_ent);

				//If it's currently colliding with something that's not itself
				if (!(mover != other_ent && isColliding(move_sprite, c_sprite) && move_collider->priority < c_collider->priority))
				{
					move_collider->normals.erase(other_ent);
				}
			}
		}
	}

	void GameSystems::ColliderSystem(Timestep dt, entt::registry& registry)
	{
		//Everything with a position and a collider needs to be considered
		auto collidables = registry.view<SpriteComponentPtr, ColliderComponentPtr>();

		auto moveables = registry.view<SpriteComponentPtr, ColliderComponentPtr, VelocityComponentPtr>();
		for (entt::entity mover : moveables)
		{
			//Get grouping for the moving entity
			auto& [move_sprite, move_collider, move_velocity] = moveables.get<SpriteComponentPtr, ColliderComponentPtr, VelocityComponentPtr>(mover);

			for (entt::entity other_ent : collidables)
			{
				//Get grouping for the entity the mover is colliding with
				auto& [c_sprite, c_collider] = collidables.get<SpriteComponentPtr, ColliderComponentPtr>(other_ent);

				//If it's currently colliding with something that's not itself
				if (mover != other_ent && isColliding(move_sprite, c_sprite) && move_collider->priority < c_collider->priority)
				{
					/*Insert a new normal or overwrite the old one*/
					sf::Vector2f normal = getNormal(move_sprite, c_sprite);

					//Assign to the mover
					move_collider->normals.insert_or_assign(other_ent, normal);


					//Also assign it to the other
					c_collider->normals.insert_or_assign(mover, -normal);

					while (isColliding(move_sprite, c_sprite))
						revertPosition(move_sprite, move_velocity, normal, dt);

				}
			}
		}
	}

	void GameSystems::CenterBackgroundOnPlayerSystem(Timestep dt, entt::registry& registry)
	{
		/* Get Player Sprite */
		auto player_view = registry.view<PlayerCharacterGroup>();
		auto player = player_view.front();
		auto& player_sprite_ptr = player_view.get<SpriteComponentPtr>(player);

		/* Get Player background*/
		auto bg_view = registry.view<BackgroundComponentPtr, SpriteComponentPtr>();
		auto bg_ent = bg_view.front();
		auto& bgSpritePtr = bg_view.get<SpriteComponentPtr>(bg_ent);

		//Center on player
		sf::Vector2f playerCtr = sf::getCenter(player_sprite_ptr->sprite);
		sf::setCenter(bgSpritePtr->sprite, playerCtr);
	}


	void GameSystems::EnemyDamageSystem(Timestep dt, entt::registry& registry)
	{

		auto enemies = registry.view<AIControllerGroup>();
		auto playerCharacter = registry.view<PlayerCharacterGroup>().front();

		auto& [pcStatus, pcCollider] = registry.get<StatusComponentPtr, ColliderComponentPtr>(playerCharacter);

		for (auto enemy_ent : enemies)
		{
			auto& collider = enemies.get<ColliderComponentPtr>(enemy_ent);
			auto& status = enemies.get<StatusComponentPtr>(enemy_ent);

			auto& pcNormals = pcCollider->normals;

			for (auto& normals : collider->normals)
			{
				//ID of the entity it's colliding with and the normal to the entity
				auto other_ent = normals.first;
				auto& normal = normals.second;

				//If the thing it has a normal to is an enemy or if the player has a normal to an enemy
				if (other_ent == playerCharacter)
				{
					if (abs(normal.y) > abs(normal.x) && normal.y < 0)
						status->Health -= pcStatus->AttackPower;
				}
			}

			//Remove it if it's dead :(
			if (status->Health <= 0)
			{
				if (pcCollider->normals.count(enemy_ent) > 0)
					pcCollider->normals.erase(enemy_ent);

				registry.remove_all(enemy_ent);
				break;
			}
			//TODO add invulnerability checks

		}
		
	}
	
	void GameSystems::ConstantRotationSystem(Timestep dt, entt::registry& registry)
	{

		//Random rotations
		const int rotationDegreesPerFrame = rand() % 2 ? 0 : 1;

		auto view = registry.view<RotationComponentPtr, SpriteComponentPtr>();

		for (auto ent : view)
		{
			auto& sprite = view.get<SpriteComponentPtr>(ent)->sprite;

			sprite.rotate(rotationDegreesPerFrame);
		}
	}

	
	void GameSystems::PositionResetSystemForPauseState(Timestep dt, entt::registry& registry)
	{
		static const int rotationDegreesPerFrame = 0.1;
		auto view = registry.view<RotationComponentPtr, SpriteComponentPtr, VelocityComponentPtr>();

		for (auto ent : view)
		{
			auto windowCenter = Renderer::GetRenderer()->getView().getCenter();
			auto windowSize = Renderer::GetRenderer()->getView().getSize();

			auto topOfWindow_Y = +windowSize.y / 2;
			auto& sprite = view.get<SpriteComponentPtr>(ent)->sprite;
			auto& velocity = view.get<VelocityComponentPtr>(ent)->velocity;
			if (!Renderer::isInWindow(sprite.getGlobalBounds()))
			{
				sprite.setPosition((float)(rand() % (int)windowSize.x), 100 - topOfWindow_Y);
				velocity.y = (float)(rand() % 1000);
			}
		}
	}


	void GameSystems::TimerDisplaySystem(Timestep dt, entt::registry& registry)
	{
		auto timer_view = registry.view<TimerComponentPtr, TextComponentPtr>();
		auto timer_entity = timer_view.front();
		auto& [timerPtr, textPtr] = timer_view.get<TimerComponentPtr, TextComponentPtr>(timer_entity);

		timerPtr->seconds_elapsed += dt;
		LOG("time elapsed: {}\n", timerPtr->seconds_elapsed);
		uint64_t whole_seconds = timerPtr->seconds_elapsed;
		std::string count = std::to_string(whole_seconds);
		if (whole_seconds >= 10) {
			count += "  LOOK OUT!";
		}
		textPtr->text.setString(count);

		// get player sprite & center above that
		auto player_view = registry.view<PlayerCharacterGroup>();
		auto player = player_view.front();
		auto& player_sprite_ptr = player_view.get<SpriteComponentPtr>(player);
		sf::Vector2f playerCtr = sf::getCenter(player_sprite_ptr->sprite);

		textPtr->text.setPosition(sf::Vector2f(playerCtr.x - 105, playerCtr.y - 113));

		//TODO have a warning, then call down the sky demons

	}

	void GameSystems::SpawnEnemiesUponTimerMax(Timestep dt, entt::registry& registry, std::shared_ptr<Scene>& scene)
	{
		static float cooldownMax = 1.0;
		static float cooldown = cooldownMax;

		if (cooldown < cooldownMax)
			cooldown += dt;

		GameSystems::ConstantRotationSystem(dt, registry);



		auto& timer = registry.get<TimerComponentPtr>(registry.view<TimerComponentPtr>().front());


		//Create a new enemy that spawns at the top and rotates if it's not on spawn cooldown
		if (timer->seconds_elapsed >= 13 && cooldown >= cooldownMax)
		{
			//Reset the cooldown
			cooldown = 0;


			float initialVelocity = (float)(rand() % 100);

			auto windowCenter = Renderer::GetRenderer()->getView().getCenter();

			auto windowSize = Renderer::GetRenderer()->getView().getSize();

			float relativePosition = (float)(rand() % (int)windowSize.x);

			//Gets the x position of the left edge of the window, and the y position of the top of the window
			auto windowLeftSide = windowCenter.x - windowSize.x / 2;
			auto topOfWindow = windowSize.y / 2;

			//Create the enemy and give it a rotation component
			std::string enemyFilepath = "resources/enemy32.png";
			Entity newEnemy = addEnemy(scene, enemyFilepath, relativePosition+windowLeftSide , 100-topOfWindow);

			GiveComponent(newEnemy, RotationComponent);
			registry.get<VelocityComponentPtr>(newEnemy.GetID())->velocity.y = initialVelocity;
		}
	}
}
