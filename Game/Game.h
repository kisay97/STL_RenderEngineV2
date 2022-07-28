#pragma once

#include <Core/Core.h>
#include <Core/Application.h>
#include <Renderer/VertexBuffer.h>
#include <Renderer/InputLayout.h>
#include <EngineShader/STLDefaultShader.h>

namespace STL 
{
	class Game : public Application
	{
	public:
		Game(
			HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title
		);

		virtual ~Game();
		virtual void Initialize() override;
		virtual void RenderScene() override;

	private:
		VertexBuffer vertexBuffer;
		InputLayout inputLayout;
		STLDefaultShader mainShader;
	};
}