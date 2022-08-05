#pragma once

#include <Core/Core.h>
#include "RTTI.h"

namespace STL
{
	// ���� ����.
	class Actor;

	class ENGINE_API Component : public RTTI
	{
		// RTTI ����.
		RTTI_DECLARATIONS(Component, RTTI)

	public:
		Component();
		virtual ~Component() = default;

		virtual void Create(ID3D11Device* device) = 0;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime = 0.0f) = 0;
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		virtual void SetActor(Actor* actor);
		virtual const Actor& GetOwnerActor() const { return *ownerActor; }

	protected:
		Actor* ownerActor;
	};
}