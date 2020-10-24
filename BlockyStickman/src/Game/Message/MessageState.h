#pragma once
#include "State.h"
#include "Scene.h"
#

namespace Blocky
{

	using ScenePtr = std::shared_ptr<Scene>;


	class DisplayMessageState : public State
	{

	public:
		DisplayMessageState(StateStack* parentRef, const std::string& message);

		virtual bool Update(Timestep dt);

		void DisplayMessageState::WaitForExit(Timestep dt, entt::registry& registry);

	private:

		ScenePtr scene;

		bool isStatePaused;

		void BackgroundAnimationSystemInit();
	};
}