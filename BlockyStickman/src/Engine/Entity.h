#pragma once

#include "entt/entt.hpp"
#include "Components.h"
#include "Scene.h"

namespace Blocky
{

	class Entity
	{

	public:


		//Essentially a wrapper to "wrap" our brains around what's going on 
		//This is kind of our own wrapper equivalent entt::basic_actor
		//But this also has a context available for the scene that it's in
		Entity() = default;

		Entity(const std::string& name);

		Entity(entt::entity eID, Scene* parent);

		entt::entity GetID() const { return m_eID; } 

		template<typename T>
		bool HasComponent(T& component)
		{
			return m_Scene->m_Registry.has<T>(component);
		}


		template<typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			m_Scene->GetRegistry().emplace<T, Args...>(m_eID, std::forward<Args>(args)...);
		}

		friend class Scene;

	private:
		entt::entity m_eID;
		Scene* m_Scene;
	};

}