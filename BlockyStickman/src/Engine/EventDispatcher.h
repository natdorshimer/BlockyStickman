#pragma once

#include "blocky-pch.h"
#include "Core.h"

namespace Blocky
{
	class EventDispatcher
	{
	public:
		EventDispatcher(sf::Event& e) :
			m_Event(e) { }

		template<sf::Event::EventType T>
		void Dispatch(const std::function<bool(sf::Event&)>& event_handler)
		{
			if (m_Event.type == T)
			{
				event_handler(m_Event);
			}
		}

	private:
		sf::Event& m_Event;

	};
}
