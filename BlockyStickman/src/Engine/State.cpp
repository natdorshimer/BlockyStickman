#include "blocky-pch.h"
#include "State.h"
#include "StateStack.h"

Blocky::State::State(StateStack* parentStack)
{
	this->parentRef =  parentStack;
}

void Blocky::State::requestStackPush(States s)
{
	parentRef->pushState(s);
}


void Blocky::State::requestStackPushFront(States s)
{
	parentRef->pushStateFront(s);
}

void Blocky::State::requestStackRemoveFront()
{
	parentRef->popFront();
}

void Blocky::State::requestStackPop()
{
	parentRef->popState();
}

void Blocky::State::requestStackClear()
{
	parentRef->clearStates();
}

void Blocky::State::requestSwap(States s)
{
	parentRef->swapStates(s);
}
