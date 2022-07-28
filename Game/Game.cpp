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

		// ��ġ ���� ����.
		auto device = deviceManager->GetDevice();

		// ���� ���� ����.
		//VertexPosition vertices[] =
		//{
		//	/*VertexPosition(-0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, -0.5f, 0.5f),
		//	VertexPosition(-0.5f, -0.5f, 0.5f),

		//	VertexPosition(-0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, -0.5f, 0.5f),*/
		//	
		//	// dx�� �޼� ��ǥ��(�޼��� ȭ�鿡 ��� ������ �� ���� ������ ���̴� ��)�� ����ϱ� ������ ���� �������� ���鼭 �׷��� �׷���.
		//	/*VertexPosition(-0.5f, 0.5f, 0.5f),
		//	VertexPosition(0.5f, -0.5f, 0.5f),
		//	VertexPosition(0.5f, 0.5f, 0.5f),*/

		//	VertexPosition(-0.5f, -0.5f, 0.5f),		// ���� �ϴ�.
		//	VertexPosition(-0.5f, 0.5f, 0.5f),		// ���� ���.
		//	VertexPosition(0.5f, 0.5f, 0.5f),		// ������ ���.
		//	VertexPosition(0.5f, -0.5f, 0.5f),		// ������ �ϴ�.
		//};

		VertexPositionColor vertices[] =
		{
			VertexPositionColor({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}),		// ���� �ϴ�.
			VertexPositionColor({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}),		// ���� ���.
			VertexPositionColor({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}),		// ������ ���.
			VertexPositionColor({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}),		// ������ �ϴ�.
		};

		vertexBuffer = VertexBuffer(vertices, _countof(vertices), sizeof(vertices[0]));
		vertexBuffer.Create(device);

		// �ε��� ���� ����.
		uint32 indices[] = { 0,1,3,1,2,3 };

		indexBuffer = IndexBuffer(indices, _countof(indices));
		indexBuffer.Create(device);

		// ���̴� �ʱ�ȭ.
		mainShader.Initialize(device);

		// �Է� ���̾ƿ� ����.
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

		// Draw �Լ��� �����ϱ� ���� GPU���� ����� ���ҽ��� ��� ���ε�(����)�Ѵ�.
		// ������ ����.
		inputLayout.Bind(context);
		vertexBuffer.Bind(context);
		mainShader.Bind(context);
		indexBuffer.Bind(context);

		// ��ο� �� (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}