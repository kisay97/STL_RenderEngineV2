#include "Game.h"
#include <Renderer/VertexDeclaration.h>

namespace STL 
{
	Game::Game(HINSTANCE hInstance, uint32 width, uint32 height, const std::wstring& title)
		: Application(hInstance, width, height, title)
	{
	}

	Game::~Game()
	{
	}

	void Game::Initialize()
	{
		Application::Initialize();

		// 장치 참조 저장.
		auto device = deviceManager->GetDevice();

		// 정점 버퍼 생성.
		VertexPosition vertices[] =
		{
			VertexPosition(0.0f, 0.5f, 0.5f),
			VertexPosition(0.5f, -0.5f, 0.5f),
			VertexPosition(-0.5f, -0.5f, 0.5f)
		};

		vertexBuffer = VertexBuffer(vertices, _countof(vertices), sizeof(vertices[0]));
		vertexBuffer.Create(device);

		// 쉐이더 초기화.
		mainShader.Initialize(device);

		// 입력 레이아웃 생성.
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), mainShader.GetVertexShaderBuffer());
	}

	void Game::RenderScene()
	{
		auto context = deviceManager->GetContext();

		// Draw 함수를 실행하기 전에 GPU에서 사용할 리소스를 모두 바인딩(연결)한다.
		// 순서는 무관.
		inputLayout.Bind(context);
		vertexBuffer.Bind(context);
		mainShader.Bind(context);

		// 드로우 콜 (Draw Call).
		context->Draw(vertexBuffer.Count(), 0);
	}
}