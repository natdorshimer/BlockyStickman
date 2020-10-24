#pragma once
#include "State.h"
#include "Scene.h"
#

namespace Blocky
{
	using ScenePtr = std::shared_ptr<Scene>;


	class PauseState : public State
	{

	public:
		PauseState(StateStack* parentRef);

		virtual bool Update(Timestep dt);

		void PauseChecker(Timestep dt, entt::registry& registry);

		void BackgroundAnimationSystemInit();

	private:

		ScenePtr scene;

		bool isStatePaused;

	};
}