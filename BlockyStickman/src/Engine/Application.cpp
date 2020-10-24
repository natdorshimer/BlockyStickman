#include "Application.h"
#include <iostream>
#include <algorithm>
#include "Core.h"
#include "Events.h"
#include "Renderer.h"

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

namespace Blocky
{
	Application::Application(std::unique_ptr<StateStack>&& gameStack) :
		m_Window(sf::VideoMode(800, 600), "Blocky"), m_StateStack(std::move(gameStack))
	{
		//Establishes the global renderer for our game
		Renderer::SetRenderer(&m_Window);

	}

	void Application::Run()
	{
		// run the program as long as the window is open
		while (m_Window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;

			//Used for updating the game logic
			Timestep dt = m_Clock.getElapsedTime().asSeconds();

			m_Clock.restart();


			//dt = 16.66667 / 1000;
			//We'll want to change this later
			while (m_Window.pollEvent(event))
			{
				//Handle event processing for the application window itself
				OnEvent(event);
			}


			//StateStack -> State -> (?World) -> Scene -> System(Entities)
			if (!m_StateStack->Update(dt))
				Shutdown();
			
			// end the current frame
			m_Window.display();
		}
	}

	void Application::Shutdown()
	{
		m_Window.close();
	}

	void Application::PushGameState(States s)
	{
		m_StateStack->pushState(s);
	}

	void Application::SetStateStack(std::unique_ptr<StateStack>&& s)
	{
		m_StateStack = std::move(s);
	}


	bool Application::OnWindowClose(sf::Event& event)
	{
		Shutdown();
		return true;
	}

	//Some way or another, events pass through here
	//Can reroute to other event handling locations
	//These test ones are currently in this file, but objects can implement their own
	void Application::OnEvent(sf::Event& event)
	{
		//The key idea behind these types of event handling is 
		auto ed = EventDispatcher(event);


		ed.Dispatch<sf::Event::KeyPressed>(BIND_EVENT(Application::OnKeyPress));

		ed.Dispatch<sf::Event::MouseButtonPressed>(BIND_EVENT(Application::OnMouseClick));

		ed.Dispatch<sf::Event::Closed>(BIND_EVENT(Application::OnWindowClose));

		//Lambdas work too
		ed.Dispatch<sf::Event::MouseMoved>([](sf::Event& e)->bool { return true; });
	}

	// It is safe to check the status of the key
	// To be deprecated or moved into a game state
	bool Application::OnKeyPress(sf::Event& event)
	{
		LOG("{}  Code:{}\n", To_String(event.type), event.key.code);
		
		return true;
	}


	bool Application::OnMouseClick(sf::Event& event)
	{
		LOG("{}: Code{} \n", To_String(event.type), event.mouseButton.button);

		return true;
	}


}

