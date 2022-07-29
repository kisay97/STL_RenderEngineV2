#include "Game.h"
#include <Renderer/VertexDeclaration.h>
#include <Utility/TextureLoader.h>
#include <Utility/STLException.h>

namespace STL 
{
	Game::Game(HINSTANCE hInstance, uint32 width, uint32 height, const std::wstring& title)
		: Application(hInstance, width, height, title)
	{
	}

	Game::~Game()
	{
		// �ε��� �ؽ�ó ���ҽ� ����.
		TextureLoader::Release();
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

		VertexPositionColorUV vertices[] =
		{
			VertexPositionColorUV({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}),		// ���� �ϴ�.
			VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}),		// ���� ���.
			VertexPositionColorUV({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}),		// ������ ���.
			VertexPositionColorUV({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),		// ������ �ϴ�.
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
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), mainShader.GetVertexShaderBuffer());

		// �ؽ�ó �ε�.
		texture = Texture(L"g4.jpg");
		texture.Create(device);

		texture2 = Texture(L"gulssi.bmp");
		texture2.Create(device);

		// ���÷� ������Ʈ ����.
		samplerState.Create(device);
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

		// �ȼ� ���̴��� �ؽ�ó ���� �ѱ�?
		texture.Bind(context, 0);
		// �ΰ�°
		texture2.Bind(context, 1);

		// ���÷� ������Ʈ ���ε�
		samplerState.Bind(context, 0);

		// ��ο� �� (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}