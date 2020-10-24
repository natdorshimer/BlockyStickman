#pragma once

#include <entt/entt.hpp>
#include "Systems.h"
#include "Entity.h"
#include "Core.h"
#include "Components.h"
#include <memory>

class Entity;

namespace Blocky
{

	/*
	* Idea behind a scene:
	*	You register an entity to the scene
	*	The scene gives you an entity to work with 
	*	You add components to the entity 
	*		Which is "really" just assigning components to the entity ID
	*	
	*	The scene has Systems that operate on the entities in the scene
	*/

	class Scene
	{


	public:


		CameraComponentPtr& RenderCamera();

		void OnUpdate(Timestep dt);

		//Wrapper for m_Registry
		Entity CreateEntity();

		void RemoveEntity(Entity e);

		void RemoveSystem(System e);

		entt::registry& GetRegistry();

		System CreateSystem(SystemFn system_func);

	private:
		entt::registry m_Registry;

		//Renders the entire scene by calling draw on all drawable objects
		void RenderScene();
	};
}