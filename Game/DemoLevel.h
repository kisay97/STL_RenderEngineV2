#pragma once

#include <Renderer/Level.h>

namespace STL
{
	// 전방선언.
	class Material;
	class DemoLevel : public Level
	{
	public:
		DemoLevel();
		~DemoLevel();

		void Initialize(ID3D11Device* device, Application* engine) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Draw(ID3D11DeviceContext* context) override;

		std::vector<Material*> materials;
	};
}