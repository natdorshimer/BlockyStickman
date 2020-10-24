#pragma once

#include "blocky-pch.h"

#ifdef BLKY_DEBUG
	#define LOG(...) fmt::print(__VA_ARGS__)
#else 
	#define LOG(...)
#endif


// In the wise words of Terry Davis, the hardest question in programming is:
// Is this too much voodoo?
#ifndef HasProperty
	#define GiveComponent(playerName, ComponentName, ...) \
		auto playerName##ComponentName = ComponentName::Create(__VA_ARGS__); \
		playerName.AddComponent<ComponentName##Ptr>(playerName##ComponentName); 
#endif

namespace Blocky
{
	using Timestep = float;

	namespace Input
	{
		const float TimeWaitForInput = 0.2f;
	}

	static const char* DefaultTextPath = "resources/stocky/stocky.ttf";
}

