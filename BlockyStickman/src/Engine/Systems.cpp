#include "blocky-pch.h"
#include "Systems.h"
#include "Scene.h"

namespace Blocky
{
	System::System(entt::entity eID, Scene* parent) :
		m_eID(eID), m_Scene(parent)
	{

	}
}