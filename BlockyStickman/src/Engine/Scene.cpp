#include "Scene.h"
#include "Entity.h"
#include "Systems.h"
#include "Renderer.h"
#include "Core.h"

namespace Blocky
{
	void RenderBottomLayer(entt::registry& registry)
	{
		auto sprite_entities = registry.view<SpriteComponentPtr, BottomLayerPtr>();

		for (auto sprite_entity : sprite_entities)
		{
			auto& sprite_c = sprite_entities.get<SpriteComponentPtr>(sprite_entity);

			Renderer::Render(sprite_c->sprite);
		}

	}

	void RenderMiddleLayer(entt::registry& registry)
	{
		auto sprite_entities = registry.view<SpriteComponentPtr, MiddleLayerPtr>();

		for (auto sprite_entity : sprite_entities)
		{
			auto& sprite_c = sprite_entities.get<SpriteComponentPtr>(sprite_entity);

			Renderer::Render(sprite_c->sprite);
		}
	}

	void RenderTopLayer(entt::registry& registry)
	{
		auto sprite_entities = registry.view<SpriteComponentPtr, TopLayerPtr>();
		auto text_entities = registry.view<TextComponentPtr, TopLayerPtr>();

		for (auto sprite_entity : sprite_entities)
		{
			auto& sprite_c = sprite_entities.get<SpriteComponentPtr>(sprite_entity);
			Renderer::Render(sprite_c->sprite);
		}

		for (auto text_entity : text_entities)
		{
			auto& text_c = text_entities.get<TextComponentPtr>(text_entity);
			Renderer::Render(text_c->text);
		}
	}

	void RenderCam(entt::registry& registry)
	{
		//Grab the camera and attach it to the renderer
		auto cameras = registry.view<CameraComponentPtr>();
		auto& cam = cameras.get<CameraComponentPtr>(cameras.back());
		Renderer::GetRenderer()->setView(cam->view);
	}

	
	void Scene::RenderScene()
	{
		
		
		Renderer::GetRenderer()->clear(sf::Color::Black);

		RenderBottomLayer(m_Registry);

		RenderMiddleLayer(m_Registry);

		RenderTopLayer(m_Registry);

		RenderCam(m_Registry);

	}

	//TODO
	CameraComponentPtr& Scene::RenderCamera()
	{
		auto entities = m_Registry.view<SpriteComponentPtr, PlayerControllerPtr, CameraComponentPtr>();

		for (auto sprite_entity : entities)
		{
			auto&[sprite, camera] = entities.get<SpriteComponentPtr, CameraComponentPtr>(sprite_entity);

			camera->view.setCenter(sprite->sprite.getPosition());

			return camera;
		}

		//TODO

		//If the other set view thing in GameState.cpp doesn't work, we'll call 

	}

	void Scene::OnUpdate(Timestep dt)
	{
		auto entities = m_Registry.view<SystemFn>();
		for (auto system_entity : entities)
		{
			auto& system = entities.get<SystemFn>(system_entity);

			//This calls all non-rendering systems
			//Translation, collision, etc
			system(dt, m_Registry);
		}
	

		//The final system
		RenderScene();
	}
	
	Entity Scene::CreateEntity()
	{
		//Put the system func into the registry
		auto eID = m_Registry.create();

		return Entity{ eID, this };
	}

	void Scene::RemoveEntity(Entity e)
	{
	    m_Registry.remove_if_exists(e.m_eID);
	}
	
	void Scene::RemoveSystem(System s)
	{
		m_Registry.remove_if_exists(s.m_eID);
	}

	entt::registry& Scene::GetRegistry()
	{
		return m_Registry;
	}

	System Scene::CreateSystem(SystemFn system_func)
	{
		//Put the system func into the registry
		auto eID = m_Registry.create();
		m_Registry.emplace<SystemFn>(eID, system_func);

		//Hand the system handle out into the world
		//They can remove it from the system later if they want
		return System(eID, this);
	}
}
