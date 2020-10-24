#include "blocky-pch.h"

#include "StateStack.h"
#include "BlockyStateStack.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "MessageState.h"


namespace Blocky
{
	 

	State::StatePtr Blocky::BlockyStateStack::GenerateState(States s)
	{
		switch (s)
		{
		case States::None:
			break;
		case States::MainMenu:
			return std::make_unique<MenuState>(this);
			break;
		case States::Game:

			//This is to let the state have a reference to the stack
			//This is so the state can tell the stack when it's state is ready to change
			//Or even specify which state it can switch to 
			return std::make_unique<GameState>(this);
			break;
		case States::Loading:
			break;
		case States::Pause:
			return std::make_unique<PauseState>(this);
			break;
		case States::GameOver:
			return std::make_unique<DisplayMessageState>(this, "GAME OVER!");
		case States::GameWon:
			return std::make_unique<DisplayMessageState>(this, "You won! :) ");
		default:
			break;
		}
	}
}
