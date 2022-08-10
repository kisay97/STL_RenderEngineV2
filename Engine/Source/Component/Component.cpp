#include "Core.h"
#include "Component.h"

#include "Actor.h"
#include "TransformComponent.h"

namespace STL
{
	Component::Component()
		: ownerActor(nullptr), transform(nullptr)
	{
	}

	void Component::SetActor(Actor* actor)
	{
		ownerActor = actor;
		transform = ownerActor->transform.get();
	}
}