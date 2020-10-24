#pragma once

#include "blocky-pch.h"
namespace Blocky
{
	std::string To_String(sf::Event::EventType t)
	{
		switch (t)
		{
		case sf::Event::EventType::Closed:
			return "Closed";
			break;
		case sf::Event::Resized:
			return "Resized";
			break;
		case sf::Event::LostFocus:
			return "LostFocus";
			break;
		case sf::Event::GainedFocus:
			return "GainedFocus";
			break;
		case sf::Event::TextEntered:
			return "TextEntered";
			break;
		case sf::Event::KeyPressed:
			return "KeyPressed";
			break;
		case sf::Event::KeyReleased:
			return "KeyReleased";
			break;
		case sf::Event::MouseWheelMoved:
			return "MouseWheelMoved";
			break;
		case sf::Event::MouseWheelScrolled:
			return "MouseWheelScrolled";
			break;
		case sf::Event::MouseButtonPressed:
			return "MouseButtonPressed";
			break;
		case sf::Event::MouseButtonReleased:
			return "MouseButtonReleased";
			break;
		case sf::Event::MouseMoved:
			return "MouseMoved";
			break;
		case sf::Event::MouseEntered:
			return "MouseEntered";
			break;
		case sf::Event::MouseLeft:
			return "MouseLeft";
			break;
		case sf::Event::JoystickButtonPressed:
			return "JoystickButtonPressed";
			break;
		case sf::Event::JoystickButtonReleased:
			return "JoystickButtonReleased";
			break;
		case sf::Event::JoystickMoved:
			return "JoystickMoved";
			break;
		case sf::Event::JoystickConnected:
			return "JoystickConnected";
			break;
		case sf::Event::JoystickDisconnected:
			return "JoystickDisconnected";
			break;
		case sf::Event::TouchBegan:
			return "TouchBegan";
			break;
		case sf::Event::TouchMoved:
			return "TouchMoved";
			break;
		case sf::Event::TouchEnded:
			return "TouchEnded";
			break;
		case sf::Event::SensorChanged:
			return "SensorChanged";
			break;
		case sf::Event::Count:
			return "Count";
			break;
		default:
			break;
		}
	}
}