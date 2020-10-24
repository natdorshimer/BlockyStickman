#pragma once


#include "Engine/Application.h"
#include "BlockyStateStack.h"

namespace Blocky
{
	 

	class BlockyStickman : public Application
	{
	public:
		BlockyStickman(std::unique_ptr<StateStack>&& gameStack) : Application(std::move(gameStack))
		{
			Init();
		}

		virtual void Init() override
		{
			PushGameState(States::MainMenu);
		}

	private:

	};
}