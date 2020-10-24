#pragma once
#include "entt/entt.hpp"
#include "Core.h"
#include "Scene.h"
namespace Blocky
{

	#define view_group_type(params) entt::basic_view<entt::entity, entt::exclude_t<>, params>

	#define PlayerCharacterGroup \
		TextureComponentPtr, SpriteComponentPtr, VelocityComponentPtr, \
		ColliderComponentPtr, PlayerControllerPtr, CameraComponentPtr, \
		StatusComponentPtr, ObjectStatePtr

	#define CollidablesGroup SpriteComponentPtr, ColliderComponentPtr
	#define MoveCollidablesGroup SpriteComponentPtr, ColliderComponentPtr, VelocityComponentPtr

	namespace GameSystems
	{
		#define RenderCameraGroup SpriteComponentPtr, PlayerControllerPtr, CameraComponentPtr
		void RenderCamera(Timestep dt, entt::registry& registry);

		//Gravity only works on airbornes!
		#define GravitySystemGroup VelocityComponentPtr, ObjectStatePtr
		void GravitySystem(Timestep dt, entt::registry& registry);

		#define TranslationSystemGroup SpriteComponentPtr, VelocityComponentPtr
		void TranslationSystem(Timestep dt, entt::registry& registry);

		#define PlayerCharacterLoggerGroup PlayerControllerPtr, SpriteComponentPtr, VelocityComponentPtr
		void PlayerCharacterLogger(Timestep dt, entt::registry& registry);

		#define MovementControllerGroup PlayerControllerPtr, SpriteComponentPtr, VelocityComponentPtr, StatusComponentPtr, ObjectStatePtr, ColliderComponentPtr

		void MovementControllerSystem(Timestep dt, entt::registry& registry);

		#define AIControllerGroup AIControllerPtr, SpriteComponentPtr, VelocityComponentPtr, StatusComponentPtr, ObjectStatePtr, ColliderComponentPtr
		//This is a basic AI controller group that controls all things with AIControllerPtr
		void AIControllerSystemBasic(Timestep dt, entt::registry& registry);

		#define PlayerDamageGroup PlayerCharacterGroup 
		//Calculates how much damage the player is supposed to take that frame
		void PlayerDamageSystem(Timestep dt, entt::registry& registry);

		//This is done at the end of each frame. It clears the collision normals for things that are not currently colliding after the translation stage
		void ClearCollisionNormals(Timestep dt, entt::registry& registry);

		//Uses AIControllerGroup
		//Tracks the damage each enemy is supposed to take
		void EnemyDamageSystem(Timestep dt, entt::registry& registry);

		//Updates the state of an object 
		void UpdateObjectState(Timestep dt, entt::registry& registry);

		//Collider system handles interactions between entities that have a ColliderComponent
		//Prevents them from touching essentially
		void ColliderSystem(Timestep dt, entt::registry& registry);

		//Forces the camera to center on the player
		void CenterBackgroundOnPlayerSystem(Timestep dt, entt::registry& registry);

		#define ConstantRotationSystemGroup RotationComponentPtr, SpriteComponentPtr
		//This introduces a constant rotation into objects that have the Rotation/Sprite group
		void ConstantRotationSystem(Timestep dt, entt::registry& registry);

		#define PositionResetSystemGroup RotationComponentPtr, SpriteComponentPtr, VelocityComponentPtr
		//This is specifically for the pause menu: when falling blockies reach the bottm, they get sent back to the top
		void PositionResetSystemForPauseState(Timestep dt, entt::registry& registry);

		//Displays the timer in the upper left of the screen
		void TimerDisplaySystem(Timestep dt, entt::registry& registry);

		//Spawns enemies after a certain elapsed time. Get to the end quickly!
		void SpawnEnemiesUponTimerMax(Timestep dt, entt::registry& registry, std::shared_ptr<Scene>& scene);
	}
}