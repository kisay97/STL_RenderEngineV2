#pragma once

#include <Core/Core.h>
#include "Component.h"

namespace STL
{
	class TransformComponent;
	class Vector3f;

	class ENGINE_API Actor
	{
	public:
		Actor(ID3D11Device* device, const std::wstring& name = L"Actor");
		virtual ~Actor();

		// 컴포넌트를 추가할 때 사용.
		void AddComponent(Component* component);

		// 액터에서 어떤 컴포넌트를 검색할 때 사용.
		// 검색에 성공하면 컴포넌트를 반환하고, 실패하면 nullptr 반환.
		template<typename T>
		T* GetComponent()
		{
			for (auto& component : components)
			{
				T* t = component->As<T>();
				if (t != nullptr)
				{
					return t;
				}
			}

			return nullptr;
		}

		virtual void Create(ID3D11Device* device);
		virtual void Update(ID3D11DeviceContext* context, float deltaTime = 0.0f);
		virtual void Bind(ID3D11DeviceContext* context);

		// 트랜스폼 정보(위치/회전/스케일) 관련 편의 함수.
		void SetPosition(float x, float y, float z);
		void SetPosition(const Vector3f& position);
		Vector3f Position() const;

		void SetRotation(float x, float y, float z);
		void SetRotation(const Vector3f& rotation);
		Vector3f Rotation() const;

		void SetScale(float x, float y, float z);
		void SetScale(const Vector3f& scale);
		Vector3f Scale() const;

		std::wstring Name() const { return name; }
		void SetName(const std::wstring& name) { this->name = name; }

		std::unique_ptr<TransformComponent> transform;

	protected:
		std::vector<Component*> components;
		std::wstring name;
	};
}