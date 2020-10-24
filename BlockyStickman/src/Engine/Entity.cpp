#include "blocky-pch.h"
#include "Entity.h"
#include "Scene.h"

Blocky::Entity::Entity(const std::string& name)
{
	//Give it a name component
	AddComponent<NameComponent>(name);
}

Blocky::Entity::Entity(entt::entity eID, Scene* parent) :
	m_eID(eID), m_Scene(parent)
{

}
