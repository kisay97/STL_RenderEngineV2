#pragma once

#include <Renderer/Level.h>

namespace STL
{
	// ���漱��.
	class Material;
	class DemoLevel : public Level
	{
	public:
		DemoLevel();
		~DemoLevel();

		void Initialize(ID3D11Device* device, Application* engine) override;

		std::vector<Material*> materials;
	};
}