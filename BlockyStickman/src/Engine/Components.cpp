#include "blocky-pch.h"
#include "Components.h"

namespace Blocky
{
	bool Blocky::ColliderComponent::hasNormals(){ return normals.size() > 0; }

	uint32_t ObjectState::GetStates()
	{
		return States;
	}


	std::string ObjectState::To_String()
	{
		std::stringstream ss;
		for (int i = 0; i < std::log2((float)GetHighestState()); i++)
		{
			auto s = (ObjStates)(1 << i);
			if (HasState((ObjStates)(1 << i)))
			{
				ss << To_String(s) << " ";
			}
		}
		return ss.str();
	}

	void ObjectState::SetState(ObjStates s)
	{
		States = ( s);
	}

	void ObjectState::RemoveState(ObjStates s)
	{
		States = (States ^ s);
	}

	void ObjectState::RemoveState()
	{
		States = 0;
	}

	bool Blocky::ObjectState::HasState(ObjStates s)
	{
		return States & s;
	}

	Blocky::ObjectState::ObjStates Blocky::ObjectState::GetHighestState()
	{
		return Standing;
	}

	bool ObjectState::HasStates(ObjectStates states)
	{
		return this->States & states;
	}

	std::string ObjectState::To_String(ObjStates s)
	{
		switch (s)
		{
		case ObjStates::Airborne:
			return "Airborne";
			break;
		case Walking:
			return "Walking";
			break;
		case Running:
			return "Invulnerable";
			break;
		case Invulnerable:
			return "Invulnerable";
			break;
		case Standing:
			return "Standing";
			break;
		default:
			return "None";
			break;

		}
	}

	

	void AIController::resetTime() { timeUntilReverse = loopLength; }

}