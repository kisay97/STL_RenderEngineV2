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
		//VertexPosition vertices[] =
		//{
		//	/*VertexPosition(-0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, -0.5f, 0.5f),
		//	VertexPosition(-0.5f, -0.5f, 0.5f),

		//	VertexPosition(-0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, -0.5f, 0.5f),*/
		//	
		//	// dx는 왼손 좌표계(왼손을 화면에 대고 말았을 때 엄지 방향이 보이는 면)를 사용하기 때문에 점이 오른쪽을 돌면서 그려야 그려짐.
		//	/*VertexPosition(-0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, -0.5f, 0.5f),
		//	VertexPosition(0.5f, 0.5f, 0.5f),*/

		//	VertexPosition(-0.5f, -0.5f, 0.5f),		// 왼쪽 하단.
		//	VertexPosition(-0.5f, 0.5f, 0.5f),		// 왼쪽 상단.
		//	VertexPosition(0.5f, 0.5f, 0.5f),		// 오른쪽 상단.
		//	VertexPosition(0.5f, -0.5f, 0.5f),		// 오른쪽 하단.
		//};

		VertexPositionColor vertices[] =
		{
			VertexPositionColor({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}),		// 왼쪽 하단.
			VertexPositionColor({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}),		// 왼쪽 상단.
			VertexPositionColor({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}),		// 오른쪽 상단.
			VertexPositionColor({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}),		// 오른쪽 하단.
		};

		vertexBuffer = VertexBuffer(vertices, _countof(vertices), sizeof(vertices[0]));
		vertexBuffer.Create(device);

		// 인덱스 버퍼 생성.
		uint32 indices[] = { 0,1,3,1,2,3 };

		indexBuffer = IndexBuffer(indices, _countof(indices));
		indexBuffer.Create(device);

		// 쉐이더 초기화.
		mainShader.Initialize(device);

		// 입력 레이아웃 생성.
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
		indexBuffer.Bind(context);

		// 드로우 콜 (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}