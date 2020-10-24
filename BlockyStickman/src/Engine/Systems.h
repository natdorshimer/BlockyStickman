#pragma once

#include "blocky-pch.h"
#include "Core.h"

namespace Blocky
{
	using SystemFn = std::function<void(Timestep, entt::registry&)>;

	class Scene;
	//System is a special type of entity and should not be confused as such
	class System
	{
		public:
			System() = default;

			System(entt::entity eID, Scene* parent);

			friend class Scene;

		private:
			entt::entity m_eID;
			Scene* m_Scene;
	};
}