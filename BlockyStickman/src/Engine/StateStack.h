#pragma once

#include "blocky-pch.h"
#include "State.h"

namespace Blocky
{
	class StateStack
	{
	public:
		void pushState(States s);

		void popState();

		void clearStates();

		bool Update(Timestep dt);

		void swapStates(States s);

		void pushStateFront(States s);

		void popFront();

	protected:
		std::vector<State::StatePtr> m_StateStack;

		virtual State::StatePtr GenerateState(States s) = 0;
	};
}