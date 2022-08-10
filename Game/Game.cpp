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
		// 로드한 텍스처 리소스 해제.
		TextureLoader::Release();
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

		// 쉐이더 초기화.
		mainShader.Initialize(device);

		// 입력 레이아웃 생성.
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), mainShader.GetVertexShaderBuffer());

		// 텍스처 로딩.
		texture = Texture(L"g4.jpg");
		texture.Create(device);

		texture2 = Texture(L"gulssi.bmp");
		texture2.Create(device);

		texture3 = Texture(L"g5.jpg");
		texture3.Create(device);

		// 샘플러 스테이트 생성.
		samplerState.Create(device);

		// 물체 생성.
		//actor1 = std::make_unique<Actor>(device);
		//actor1->Create(device);
		//actor1->SetScale(0.5f, 0.5f, 1.0f); //x,y 스케일을 1/2로 축소
		//actor1->SetPosition(-0.5f, 0.0f, 0.5f); //물체 위치를 왼쪽으로 0.5만큼 이동.

		//actor2 = std::make_unique<Actor>(device);
		//actor2->Create(device);
		//actor2->SetScale(0.5f, 0.5f, 1.0f); //x,y 스케일을 1/2로 축소
		//actor2->SetPosition(0.5f, 0.0f, 0.5f); //물체 위치를 오른쪽으로 0.5만큼 이동.
		
		// 레벨 초기화
		mainLevel.Initialize(device, this);
	}

	void Game::Update(float deltaTime)
	{
		// 레벨 업데이트.
		auto context = deviceManager->GetContext();
		mainLevel.Update(context, deltaTime);

		//// 이동 예제
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

		// Draw 함수를 실행하기 전에 GPU에서 사용할 리소스를 모두 바인딩(연결)한다.
		// 순서는 무관.
		inputLayout.Bind(context);
		//vertexBuffer.Bind(context);
		mainShader.Bind(context);
		//indexBuffer.Bind(context);

		// 픽셀 쉐이더에 텍스처 정보 넘김?
		texture.Bind(context, 0);
		// 두개째
		texture2.Bind(context, 1);

		// 샘플러 스테이트 바인드
		samplerState.Bind(context, 0);

		mainLevel.Bind(context);
		mainLevel.Draw(context);

		// 트랜스폼 버퍼 바인드
		//transformBuffer.Bind(context, 0);
		//actor1->Bind(context);

		//// 드로우 콜 (Draw Call).
		////context->Draw(vertexBuffer.Count(), 0);
		//context->DrawIndexed(indexBuffer.Count(), 0u, 0u);

		//texture3.Bind(context, 0);
		//actor2->Bind(context);
		//context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}