#include "DemoLevel.h"

#include <Component/Actor.h>
#include <Component/TransformComponent.h>
#include <Component/StaticMeshComponent.h>

#include <Renderer/VertexDeclaration.h>

#include <Math/MathHelper.h>
#include <Component/CameraComponent.h>

#include <Core/Application.h>		// 엔진 기능 사용을 위해.

#include "CameraController.h"

#include <Material/Material.h>
#include <Material/TransformMaterial.h>
#include <Material/DiffuseMaterial.h>
#include <Material/DiffuseSpecularMaterial.h>

#include <Utility/ModelLoader.h>

#include "SoldierActor.h"
#include "SquidGameActor.h"
#include <Component/LightComponent.h>

namespace STL
{
	DemoLevel::DemoLevel()
		: Level()
	{
	}

	DemoLevel::~DemoLevel()
	{
		for (auto material : materials)
		{
			if (material != nullptr)
			{
				delete material;
				material = nullptr;
			}
		}
	}

	void DemoLevel::Initialize(ID3D11Device* device, Application* engine)
	{
		//VertexPositionColorUVNormal vertices[] =
		//{
		//	VertexPositionColorUVNormal({ -0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, {0.0f, 0.0f, -1.0f}),		// 왼쪽 하단.
		//	VertexPositionColorUVNormal({ -0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, {0.0f, 0.0f, -1.0f}),		// 왼쪽 상단.
		//	VertexPositionColorUVNormal({ 0.5f,  0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }, {0.0f, 0.0f, -1.0f}),		// 오른쪽 상단.
		//	VertexPositionColorUVNormal({ 0.5f, -0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.0f, 0.0f, -1.0f}),		// 오른쪽 하단.
		//};

		//uint32 indices[] = { 0, 1, 3, 1, 2, 3 };

		//// 머티리얼 생성.
		//TransformMaterial* transformMaterial = new TransformMaterial();
		//transformMaterial->AddTexture(new Texture(L"sample.jpg"));
		//materials.emplace_back(transformMaterial);

		//// Actor1 구성.
		//Actor* actor = new Actor(device);
		//actor->SetPosition(-0.5f, 0.0f, 0.0f);
		//actor->SetScale(0.5f, 0.5f, 1.0f);
		//
		//auto meshComponent = new StaticMeshComponent();
		//meshComponent->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
		//	indices, _countof(indices), sizeof(uint32));
		//meshComponent->AddMaterial(transformMaterial);
		//actor->AddComponent(meshComponent);

		//// Actor2 구성.
		//Actor* actor2 = new Actor(device);
		//actor2->SetPosition(0.5f, 0.0f, 0.0f);
		//actor2->SetScale(0.5f, 0.5f, 1.0f);

		//auto meshComponent2 = new StaticMeshComponent();
		//meshComponent2->Create(device, vertices, _countof(vertices), sizeof(vertices[0]),
		//	indices, _countof(indices), sizeof(uint32));
		//meshComponent2->AddMaterial(transformMaterial);
		//actor2->AddComponent(meshComponent2);

		// 카메라 추가.
		Actor* cameraActor = new Actor(device);
		cameraActor->SetPosition(0.0f, 100.0f, -200.0f);
		cameraActor->AddComponent(new CameraComponent(
			60.0f * MathHelper::Deg2Rad,			// 시야각 설정 (60도).
			static_cast<uint32>(engine->Width()),	// 가로 크기.
			static_cast<uint32>(engine->Height()),	// 세로 크기.
			0.1f,									// 근평면 거리.
			1000.0f									// 원평면 거리.
		));

		// 카메라 컨트롤러 생성 및 컴포넌트 추가.
		auto cameraController = new CameraController();
		cameraController->SetKeyboard(engine->GetKeyboard());
		cameraController->SetMouse(engine->GetMouse());
		cameraController->SetMoveSpeed(100.0f);		// 이동 속도.
		cameraActor->AddComponent(cameraController);

		// 군인.
		// 스태틱 메시 로드.
		StaticMesh* soldierMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "Soldier.fbx", soldierMesh);

		// 머티리얼 생성.
		auto soldierBodyMaterial = new DiffuseSpecularMaterial();
		//auto soldierBodyMaterial = new DiffuseMaterial();
		soldierBodyMaterial->AddTexture(new Texture(L"Soldier_Body_diffuse.png"));
		soldierBodyMaterial->AddTexture(new Texture(L"Soldier_Body_specular.png"));
		soldierBodyMaterial->Initialize(device);
		materials.emplace_back(soldierBodyMaterial);

		auto soldierHeadMaterial = new DiffuseSpecularMaterial();
		//auto soldierHeadMaterial = new DiffuseMaterial();
		soldierHeadMaterial->AddTexture(new Texture(L"Soldier_head_diffuse.png"));
		soldierHeadMaterial->AddTexture(new Texture(L"Soldier_head_specular.png"));
		soldierHeadMaterial->Initialize(device);
		materials.emplace_back(soldierHeadMaterial);

		SoldierActor* soldierActor = new SoldierActor(device);
		soldierActor->SetStaticMesh(soldierMesh);
		soldierActor->SetMaterial(soldierBodyMaterial, soldierHeadMaterial);

		// 오징어 게임 액터 추가.
		// 스태틱 메시 로드.
		StaticMesh* squidGameMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh);

		// 머티리얼 생성.
		auto squidGameMat1 = new DiffuseSpecularMaterial();
		squidGameMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat1->Initialize(device);
		materials.emplace_back(squidGameMat1);

		auto squidGameMat2 = new DiffuseSpecularMaterial();
		squidGameMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat2->Initialize(device);
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
		auto lightComponent = lightActor->GetComponent<LightComponent>();
		lightComponent->SetLightColor({ 1.0f, 1.0f, 1.0f });

		// 레벨에 액터 추가.
		//AddActor(actor);
		//AddActor(actor2);
		AddActor(cameraActor);
		AddActor(soldierActor);
		AddActor(squidGameActor);
		AddActor(lightActor);

		Level::Initialize(device, engine);
	}
	
	void DemoLevel::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		Level::Update(context, deltaTime);
	}
	
	void DemoLevel::Draw(ID3D11DeviceContext* context)
	{
		Level::Draw(context);
	}
}