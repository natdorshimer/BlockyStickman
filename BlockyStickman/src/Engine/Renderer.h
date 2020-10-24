#pragma once

#include "blocky-pch.h"

namespace Blocky
{
	//Essentially a global renderer
	//Can add more graphics information if needed
	//TODO: Maybe make this a singleton class
	class Renderer
	{
	public:

		static void Render(sf::Drawable& d);

		static void SetRenderer(sf::RenderWindow* m_Window);

		static sf::RenderWindow* GetRenderer();

		static bool isInWindow(sf::FloatRect bounds);

	private:

		//TODO, maybe shared ptr
		static inline sf::RenderWindow* mainRenderWindow;
	}; 

}