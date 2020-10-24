#include "blocky-pch.h"
#include "StateStack.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "MessageState.h"
namespace Blocky
{
	void StateStack::pushState(States s)
	{
		m_StateStack.push_back(std::move(GenerateState(s)));
	}

	void StateStack::popState()
	{
		m_StateStack.pop_back();
	}

	
	void StateStack::pushStateFront(States s)
	{
		m_StateStack.insert(m_StateStack.begin(), std::move(GenerateState(s)));
	}

	void StateStack::popFront()
	{
		LOG("Removing State Stack Front\n");
		m_StateStack.erase(m_StateStack.begin());
	}

	void StateStack::clearStates()
	{
		m_StateStack.clear();
	}

	bool StateStack::Update(Timestep dt)
	{
		//TODO : might only want to do one, or the top one

		//If there's nothing to render, the application is over and it'll return false
		if (m_StateStack.size() == 0)
			return false;

		size_t initial_size = m_StateStack.size();
		for (auto stateItr = m_StateStack.rbegin(); stateItr != m_StateStack.rend(); stateItr++)
		{
			//If the state returns false on update, don't continue through the stack
			if (!((*stateItr)->Update(dt)))
					break;

			if (m_StateStack.size() != initial_size)
				break;
		}

		return true;
	}

	void StateStack::swapStates(States s)
	{
		//Please don't call this unless you have something to swap
		assert(m_StateStack.size() >= 1);

		m_StateStack.push_back(GenerateState(s));
		std::swap(*(m_StateStack.end()-1), *(m_StateStack.end() - 2));
		m_StateStack.pop_back();
	}

	State::StatePtr StateStack::GenerateState(States s)
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