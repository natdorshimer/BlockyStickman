#pragma once
#include "Core.h"
#include <memory>


namespace Blocky
{
	//Ex: States are as follows

	//None MainMenu Loading Game

	//Current stack is Game
	//Say you press pause

	//State stack becomes
	//None  MainMenu Loading Game Pause
	//Then pause is the current game state until it's popped off of the stack

	enum class States
	{
		None = 0,
		MainMenu,
		Game,
		Loading,
		Pause,
		GameOver,
		GameWon
	};

	class StateStack;

	// Generic state to inherit from. Provides functionality for state switching
	class State
	{
	public:


		State(StateStack* parentStack);

		//State -> (if?World) -> Scene -> System(Entities)
		virtual bool Update(Timestep dt) = 0;

		//States are unique, only the StateStack can take control of them
		using StatePtr = std::unique_ptr<State>;

		//To push a new state onto the stack to handle
		virtual void requestStackPush(States s);
		
		//virtual void requestStackPushFront(States s);

		//virtual void requestStackRemoveFront();

		virtual void requestStackPop();

		virtual void requestStackClear();

		virtual void requestSwap(States s);

	private:
		StateStack* parentRef; //Not responsible for parent's lifetime, just a reference
	};
}