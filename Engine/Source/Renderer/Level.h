#pragma once

#include <Core/Core.h>

namespace STL
{
	class Actor;
	class Application;
	class ENGINE_API Level
	{
	public:
		Level();
		virtual ~Level();

		void AddActor(Actor* entity);
		virtual void Initialize(ID3D11Device* device, Application* engine);
		virtual void Update(ID3D11DeviceContext* context, float deltaTime);
		virtual void Bind(ID3D11DeviceContext* context);
		virtual void Draw(ID3D11DeviceContext* context);

	protected:
		std::vector<Actor*> actors;
		Actor* mainCamera;
	};
}