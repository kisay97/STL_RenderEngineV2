#include "Game.h"
#include <Renderer/VertexDeclaration.h>
#include <Utility/TextureLoader.h>
#include <Utility/STLException.h>
#include <Math/MathHelper.h>

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

		texture3 = Texture(L"g5.jpg");
		texture3.Create(device);

		// ���÷� ������Ʈ ����.
		samplerState.Create(device);

		// ��ü ����.
		//actor1 = std::make_unique<Actor>(device);
		//actor1->Create(device);
		//actor1->SetScale(0.5f, 0.5f, 1.0f); //x,y �������� 1/2�� ���
		//actor1->SetPosition(-0.5f, 0.0f, 0.5f); //��ü ��ġ�� �������� 0.5��ŭ �̵�.

		//actor2 = std::make_unique<Actor>(device);
		//actor2->Create(device);
		//actor2->SetScale(0.5f, 0.5f, 1.0f); //x,y �������� 1/2�� ���
		//actor2->SetPosition(0.5f, 0.0f, 0.5f); //��ü ��ġ�� ���������� 0.5��ŭ �̵�.
		
		// ���� �ʱ�ȭ
		mainLevel.Initialize(device, this);
	}

	void Game::Update(float deltaTime)
	{
		// ���� ������Ʈ.
		auto context = deviceManager->GetContext();
		mainLevel.Update(context, deltaTime);

		//// �̵� ����
		//static float alpha = 0.0f;
		//static float sign = 1.0f;
		//static float moveSpeed = 0.5f;
		//static float actorOffset = actor1->Position().x;
		//static float actorOffset2 = actor2->Position().x;
		//alpha += moveSpeed * deltaTime * sign;
		//if (deltaTime > 1.0f)
		//{
		//	alpha = 0.0f;
		//}

		//if (alpha > 1.0f)
		//{
		//	sign = -1.0f;
		//}

		//if (alpha < 0.0f)
		//{
		//	sign = 1.0f;
		//}

		//static float xStart = -0.5f;
		//static float xEnd = 0.5f;

		//float xPosition = MathHelper::Lerpf(xStart, xEnd, alpha);
		//actor1->SetPosition(xPosition + actorOffset + 0.2f, 0.0f, 0.2f);
		//actor2->SetPosition(0.0f, xPosition + actorOffset2 - 0.2f, 0.0f);

		//auto context = deviceManager->GetContext();
		//actor1->Update(context, deltaTime);
		//actor2->Update(context, deltaTime);
	}

	void Game::RenderScene()
	{
		auto context = deviceManager->GetContext();

		// Draw �Լ��� �����ϱ� ���� GPU���� ����� ���ҽ��� ��� ���ε�(����)�Ѵ�.
		// ������ ����.
		inputLayout.Bind(context);
		//vertexBuffer.Bind(context);
		mainShader.Bind(context);
		//indexBuffer.Bind(context);

		// �ȼ� ���̴��� �ؽ�ó ���� �ѱ�?
		texture.Bind(context, 0);
		// �ΰ�°
		texture2.Bind(context, 1);

		// ���÷� ������Ʈ ���ε�
		samplerState.Bind(context, 0);

		mainLevel.Bind(context);
		mainLevel.Draw(context);

		// Ʈ������ ���� ���ε�
		//transformBuffer.Bind(context, 0);
		//actor1->Bind(context);

		//// ��ο� �� (Draw Call).
		////context->Draw(vertexBuffer.Count(), 0);
		//context->DrawIndexed(indexBuffer.Count(), 0u, 0u);

		//texture3.Bind(context, 0);
		//actor2->Bind(context);
		//context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}