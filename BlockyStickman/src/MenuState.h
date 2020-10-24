#pragma once
#include <map>
#include "Core.h"
#include "Entity.h"
#include "Scene.h"
#include <memory>
#include "State.h"


namespace Blocky
{
	using ScenePtr = std::shared_ptr<Scene>;

	class MenuState : public State
	{
	public:
		MenuState(StateStack* parentRef);

		virtual bool Update(Timestep dt);

	private:
		ScenePtr scene;
	};
}