#include "Core.h"
#include "Actor.h"
#include "TransformComponent.h"
#include <Math/Vector3f.h>

namespace STL
{
	Actor::Actor(ID3D11Device* device, const std::wstring& name)
		: name(name)
	{
		// 트랜스폼 컴포넌트 생성.
		transform = std::make_unique<TransformComponent>();
		transform->Create(device);
	}

	Actor::~Actor()
	{
		// 액터가 가진 컴포넌트들을 모두 해제.
		for (auto component : components)
		{
			if (component != nullptr)
			{
				delete component;
				component = nullptr;
			}
		}
	}
	
	// 액터에 컴포넌트 추가하는 함수.
	void Actor::AddComponent(Component* component)
	{
		// 컴포넌트에 소유자 액터 설정.
		component->SetActor(this);

		// 컴포넌트 배열에 새로 추가.
		components.emplace_back(component);
	}
	
	void Actor::Create(ID3D11Device* device)
	{
		// 트랜스폼 업데이트.
		transform->Create(device);

		// 컴포넌트의 Create 간접 호출.
		for (const auto component : components)
		{
			component->Create(device);
		}
	}
	
	void Actor::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// 트랜스폼 업데이트.
		transform->Update(context, deltaTime);

		// 컴포넌트의 Update 간접 호출.
		for (const auto component : components)
		{
			component->Update(context,deltaTime);
		}
	}
	
	void Actor::Bind(ID3D11DeviceContext* context)
	{
		// 트랜스폼 Bind.
		transform->Bind(context);

		// 컴포넌트의 Update 간접 호출.
		for (const auto component : components)
		{
			component->Bind(context);
		}
	}
	
	void Actor::SetPosition(float x, float y, float z)
	{
		transform->SetPosition(x, y, z);
	}
	
	void Actor::SetPosition(const Vector3f& position)
	{
		transform->SetPosition(position);
	}
	
	Vector3f Actor::Position() const
	{
		return transform->Position();
	}
	
	void Actor::SetRotation(float x, float y, float z)
	{
		transform->SetRotation(x, y, z);
	}
	
	void Actor::SetRotation(const Vector3f& rotation)
	{
		transform->SetRotation(rotation);
	}
	
	Vector3f Actor::Rotation() const
	{
		return transform->Rotation();
	}
	
	void Actor::SetScale(float x, float y, float z)
	{
		transform->SetScale(x, y, z);
	}
	
	void Actor::SetScale(const Vector3f& scale)
	{
		transform->SetScale(scale);
	}
	
	Vector3f Actor::Scale() const
	{
		return transform->Scale();
	}
}