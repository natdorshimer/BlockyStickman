#pragma once
#include "StateStack.h"

namespace Blocky
{
	 
	class BlockyStateStack : public StateStack
	{
	public:

	protected:
		virtual State::StatePtr GenerateState(States s) override;
	};
}