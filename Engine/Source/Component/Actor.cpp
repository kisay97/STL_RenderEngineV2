#include "Core.h"
#include "Actor.h"
#include "TransformComponent.h"
#include <Math/Vector3f.h>

namespace STL
{
	Actor::Actor(ID3D11Device* device, const std::wstring& name)
		: name(name)
	{
		// Ʈ������ ������Ʈ ����.
		transform = std::make_unique<TransformComponent>();
		transform->Create(device);
	}

	Actor::~Actor()
	{
		// ���Ͱ� ���� ������Ʈ���� ��� ����.
		for (auto component : components)
		{
			if (component != nullptr)
			{
				delete component;
				component = nullptr;
			}
		}
	}
	
	// ���Ϳ� ������Ʈ �߰��ϴ� �Լ�.
	void Actor::AddComponent(Component* component)
	{
		// ������Ʈ�� ������ ���� ����.
		component->SetActor(this);

		// ������Ʈ �迭�� ���� �߰�.
		components.emplace_back(component);
	}
	
	void Actor::Create(ID3D11Device* device)
	{
		// Ʈ������ ������Ʈ.
		transform->Create(device);

		// ������Ʈ�� Create ���� ȣ��.
		for (const auto component : components)
		{
			component->Create(device);
		}
	}
	
	void Actor::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// Ʈ������ ������Ʈ.
		transform->Update(context, deltaTime);

		// ������Ʈ�� Update ���� ȣ��.
		for (const auto component : components)
		{
			component->Update(context,deltaTime);
		}
	}
	
	void Actor::Bind(ID3D11DeviceContext* context)
	{
		// Ʈ������ Bind.
		transform->Bind(context);

		// ������Ʈ�� Update ���� ȣ��.
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