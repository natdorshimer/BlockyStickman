#include <iostream>
#include <SFML/Graphics.hpp>
#include "Application.h"
#include "Core.h"
#include <fmt/format.h>

#include <entt/entt.hpp>
#include <cstdint>

#include "BlockyStateStack.h"
#include "BlockyStickman-App.h"
#include <memory>

 
int main()
{
	Blocky::BlockyStickman app(std::make_unique<Blocky::BlockyStateStack>());

	app.Run();
}

