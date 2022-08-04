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

		VertexPositionColorUV vertices[] =
		{
			VertexPositionColorUV({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}),		// 왼쪽 하단.
			VertexPositionColorUV({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}),		// 왼쪽 상단.
			VertexPositionColorUV({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}),		// 오른쪽 상단.
			VertexPositionColorUV({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}),		// 오른쪽 하단.
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
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		inputLayout.Create(device, layout, _countof(layout), mainShader.GetVertexShaderBuffer());

		// 텍스처 로딩.
		texture = Texture(L"g4.jpg");
		texture.Create(device);

		texture2 = Texture(L"gulssi.bmp");
		texture2.Create(device);

		// 샘플러 스테이트 생성.
		samplerState.Create(device);

		// 위치 행렬만 적용해서 월드 행렬 생성.
		worldMatrix = Matrix4f::Translation(position);
		// 월드 행렬을 데이터로 상수 버퍼 생성.
		transformBuffer = ConstantBuffer(&worldMatrix, 1, sizeof(worldMatrix));
		transformBuffer.Create(device);

		/*rotation.z = -45.0f;
		scale.x = 0.5f;
		position.y = 0.5f;*/
	}

	void Game::Update(float deltaTime)
	{
		// 왔다갔다 하는 예제
		static float alpha = 0.0f;
		static float sign = 1.0f;
		alpha += 0.5f * deltaTime * sign;
		if (deltaTime > 1.0f)
		{
			alpha = 0.0f;
		}

		if (alpha > 1.0f)
		{
			sign = -1.0f;
		}

		if (alpha < 0.0f)
		{
			sign = 1.0f;
		}

		static float xStart = -0.5f;
		static float xEnd = 0.5f;

		float xPosition = MathHelper::Lerpf(xStart, xEnd, alpha);
		position.x = xPosition;
		
		rotation.z += 3.0f;

		scale.x = xPosition;
		scale.y = xPosition;

		// 위치/회전/스케일 값을 적용해서 월드 행렬 데이터 업데이트
		worldMatrix = Matrix4f::Scale(scale)
			* Matrix4f::Rotation(rotation)
			* Matrix4f::Translation(position);

		// 갱신된 월드 행렬 데이터로 상수 버퍼 업데이트.
		transformBuffer.Update(deviceManager->GetContext(), &worldMatrix);
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

		// 픽셀 쉐이더에 텍스처 정보 넘김?
		texture.Bind(context, 0);
		// 두개째
		texture2.Bind(context, 1);

		// 샘플러 스테이트 바인드
		samplerState.Bind(context, 0);

		// 트랜스폼 버퍼 바인드
		transformBuffer.Bind(context, 0);

		// 드로우 콜 (Draw Call).
		//context->Draw(vertexBuffer.Count(), 0);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0u);
	}
}