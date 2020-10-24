#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <functional>
#include "EventDispatcher.h"
#include "StateStack.h"


namespace Blocky
{
	class Application
	{
	public:
		Application(std::unique_ptr<StateStack>&& gameStack);

		void Run();

		//This is staying
		void OnEvent(sf::Event& event);

		void Shutdown();

		virtual void Init() = 0;

	protected:
		
		void PushGameState(States s);

		void SetStateStack(std::unique_ptr<StateStack>&& s);

	private: 
		
		bool OnWindowClose(sf::Event& event);

		//These are kind of just test functions for now, likely moving elsewhere
		bool OnKeyPress(sf::Event& event);

		//Or maybe they will stay here, kind of depends on the direction
		bool OnMouseClick(sf::Event& event);

		sf::RenderWindow m_Window;

		//Contains a list of game states
		std::unique_ptr<StateStack> m_StateStack;

		sf::Clock m_Clock;
	};

}