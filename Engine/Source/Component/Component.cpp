#include "Core.h"
#include "Component.h"

namespace STL
{
	Component::Component()
		: ownerActor(nullptr)
	{
	}

	void Component::SetActor(Actor* actor)
	{
		ownerActor = actor;
	}
}