#include "DemoLevel.h"

#include <Component/Actor.h>
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>
#include <Component/CameraComponent.h>

#include <Renderer/VertexDeclaration.h>

#include <Math/MathHelper.h>

#include <Core/Application.h> // 엔진 기능 사용을 위해.

#include "CameraController.h"

#include <Material/Material.h>
#include <Material/TransformMaterial.h>
#include <Material/DiffuseMaterial.h>

#include <Utility/ModelLoader.h>
#include "SoldierActor.h"
#include "SquidGameActor.h"
#include <Component/LightComponent.cpp>

namespace STL
{
	DemoLevel::DemoLevel()
		: Level()
	{
	}
	DemoLevel::~DemoLevel()
	{
	}
	void DemoLevel::Initialize(ID3D11Device* device, Application* engine)
	{
		VertexPositionColorUVNormal vertices[] =
		{
			VertexPositionColorUVNormal({-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}),		// 왼쪽 하단.
			VertexPositionColorUVNormal({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}),		// 왼쪽 상단.
			VertexPositionColorUVNormal({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}),		// 오른쪽 상단.
			VertexPositionColorUVNormal({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}),		// 오른쪽 하단.
		};

		uint32 indices[] = { 0,1,3,1,2,3 };

		// 머티리얼 생성.
		TransformMaterial* transformMaterial = new TransformMaterial();
		transformMaterial->AddTexture(new Texture(L"g4.jpg"));
		//transformMaterial->AddTexture(new Texture(L"g5.jpg"));
		transformMaterial->AddTexture(new Texture(L"gulssi.bmp"));
		materials.emplace_back(transformMaterial);

		// actor1 구성.
		Actor* actor = new Actor(device);
		actor->SetPosition(-0.5f, 0.0f, 0.0f);
		actor->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent = new StaticMeshComponent();
		meshComponent->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		meshComponent->AddMaterial(transformMaterial);
		actor->AddComponent(meshComponent);

		// actor2 구성.
		Actor* actor2 = new Actor(device);
		actor2->SetPosition(0.5f, 0.0f, 0.0f);
		actor2->SetScale(0.5f, 0.5f, 1.0f);

		auto meshComponent2 = new StaticMeshComponent();
		meshComponent2->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
			indices, _countof(indices), sizeof(uint32));
		meshComponent2->AddMaterial(transformMaterial);
		actor2->AddComponent(meshComponent2);

		// 카메라 추가.
		Actor* cameraActor = new Actor(device);
		cameraActor->SetPosition(0.0f, 100.0f, -200.0f);
		cameraActor->AddComponent(new CameraComponent(
			60.0f * MathHelper::Deg2Rad, // 시야각 설정 (반각이 60도. 전체 120도).
			static_cast<uint32>(engine->Width()), // 가로 크기
			static_cast<uint32>(engine->Height()), // 세로 크기.
			0.1f, // 근평면 거리.
			1000.0f // 원평면 거리.
		));

		// 카메라 컨트롤러 생성 및 컴포넌트 추가.
		auto cameraController = new CameraController();
		cameraController->SetKeyboard(engine->GetKeyboard());
		cameraController->SetMouse(engine->GetMouse());
		cameraController->SetMoveSpeed(100.0f); // 이동 속도.
		cameraActor->AddComponent(cameraController);

		// 군인.
		// 스태틱 메시 로드.
		StaticMesh* soldierMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "Soldier.fbx", soldierMesh);

		// 머티리얼 생성.
		auto soldierBodyMaterial = new DiffuseMaterial();
		soldierBodyMaterial->AddTexture(new Texture(L"Soldier_Body_diffuse.png"));
		soldierBodyMaterial->Initialize(device);
		materials.emplace_back(soldierBodyMaterial);

		auto soldierHeadMaterial = new DiffuseMaterial();
		soldierHeadMaterial->AddTexture(new Texture(L"Soldier_head_diffuse.png"));
		soldierHeadMaterial->Initialize(device);
		materials.emplace_back(soldierHeadMaterial);

		// 액터 생성 및 초기화.
		//Actor* soldierActor = new Actor(device);
		//// 액터에 스태틱 메시 컴포넌트 추가.
		//soldierActor->AddComponent(new StaticMeshComponent());
		//// 추가한 메시 컴포넌트 검색.
		//auto soldierMeshComponent = soldierActor->GetComponent<StaticMeshComponent>();
		//// 스태틱 메시 컴포넌트에 스태틱 메시 설정.
		//soldierMeshComponent->SetStaticMesh(soldierMesh);
		//// 필요한 머티리얼 추가.
		//soldierMeshComponent->AddMaterial(soldierBodyMaterial);
		//soldierMeshComponent->AddMaterial(soldierHeadMaterial);
		//soldierMeshComponent->AddMaterial(soldierBodyMaterial);

		SoldierActor* soldierActor = new SoldierActor(device);
		soldierActor->SetStaticMesh(soldierMesh);
		soldierActor->SetMaterial(soldierBodyMaterial, soldierHeadMaterial);

		// 오징어 게임 액터 추가.
		// 스태틱 메시 로드.
		StaticMesh* squidGameMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh);
		
		// 머티리얼 생성.
		auto squidGameMat1 = new DiffuseMaterial();
		squidGameMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		materials.emplace_back(squidGameMat1);

		auto squidGameMat2 = new DiffuseMaterial();
		squidGameMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		materials.emplace_back(squidGameMat2);

		// 액터 생성 및 설정.
		SquidGameActor* squidGameActor = new SquidGameActor(device);
		squidGameActor->SetPosition(200.0f, 0.0f, 0.0f);
		squidGameActor->SetStaticMesh(squidGameMesh);
		squidGameActor->SetMaterials(squidGameMat1, squidGameMat2);

		// 라이트 액터 생성.
		Actor* lightActor = new Actor(device);
		lightActor->SetPosition(500.0f, 500.0f, -500.0f);
		lightActor->AddComponent(new LightComponent());

		// 레벨에 액터 추가
		AddActor(actor);
		AddActor(actor2);
		AddActor(cameraActor);
		AddActor(soldierActor);
		AddActor(squidGameActor);
		AddActor(lightActor);

		Level::Initialize(device, engine);
	}
}