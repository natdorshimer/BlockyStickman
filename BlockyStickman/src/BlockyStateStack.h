#pragma once

#include "State.h"

namespace Blocky
{
	 
	class BlockyStateStack : public StateStack
	{
	public:

	protected:
		virtual State::StatePtr GenerateState(States s) override;
	};
}