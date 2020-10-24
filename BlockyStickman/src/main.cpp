#include "blocky-pch.h"
#include <iostream>
#include "Application.h"
#include "Core.h"

#include "BlockyStateStack.h"
#include "BlockyStickman-App.h"

 
int main()
{
	Blocky::BlockyStickman app(std::make_unique<Blocky::BlockyStateStack>());

	app.Run();
}

