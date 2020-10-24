#pragma once
#include "entt/entt.hpp"
#include "Core.h"
#include "State.h"

namespace Blocky
{
	 
	namespace MenuSystems
	{
		// gets user selection via the mouse (or keyboard, tbd)
		void SelectionReportSystem(Timestep dt, entt::registry& registry, State* currentState);
		void RenderCamera(Timestep dt, entt::registry& registry);
	}

}
