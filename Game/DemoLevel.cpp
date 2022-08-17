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
#include <Material/NormalMappingMaterial.h>
#include <Material/CubeMapMaterial.h>
#include <Material/RimMaterial.h>
#include <Material/RimNormalMappingMaterial.h>

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
		// 카메라 추가.
		Actor* cameraActor = new Actor(device);
		cameraActor->SetPosition(0.0f, 100.0f, -500.0f);
		cameraActor->AddComponent(new CameraComponent(
			60.0f * MathHelper::Deg2Rad,			// 시야각 설정 (60도).
			static_cast<uint32>(engine->Width()),	// 가로 크기.
			static_cast<uint32>(engine->Height()),	// 세로 크기.
			0.1f,									// 근평면 거리.
			100000.0f									// 원평면 거리.
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
		//soldierActor->SetRotation({ -90.0f, 0.0f, 0.0f });

		// 오징어 게임 액터 추가.
		// 스태틱 메시 로드.
		StaticMesh* squidGameMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh);

		// 머티리얼 생성.
		auto squidGameMat1 = new DiffuseSpecularMaterial();
		squidGameMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat1->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat1->SetShiness(100.0f); // 블린 퐁 방식일 때 Shiness를 더 줘야 하는데(그냥 퐁 방식이면 32임) 100을 줌
		squidGameMat1->Initialize(device);
		materials.emplace_back(squidGameMat1);

		auto squidGameMat2 = new DiffuseSpecularMaterial();
		squidGameMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat2->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat2->SetShiness(100.0f); // 블린 퐁 방식일 때 Shiness를 더 줘야 하는데(그냥 퐁 방식이면 32임) 100을 줌
		squidGameMat2->Initialize(device);
		materials.emplace_back(squidGameMat2);

		// 액터 생성 및 설정.
		SquidGameActor* squidGameActor = new SquidGameActor(device);
		squidGameActor->SetPosition(-300.0f, 0.0f, 0.0f);
		squidGameActor->SetStaticMesh(squidGameMesh);
		squidGameActor->SetMaterials(squidGameMat1, squidGameMat2);

		StaticMesh* squidGameMesh2 = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh2);

		// 머티리얼 생성.
		auto squidGameMat3 = new NormalMappingMaterial();
		squidGameMat3->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat3->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat3->AddTexture(new Texture(L"PinkSoldier_Normal_1001.png"));
		squidGameMat3->SetShiness(100.0f);
		squidGameMat3->Initialize(device);
		materials.emplace_back(squidGameMat3);

		auto squidGameMat4 = new NormalMappingMaterial();
		squidGameMat4->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat4->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat4->AddTexture(new Texture(L"PinkSoldier_Normal_1002.png"));
		squidGameMat4->SetShiness(100.0f);
		squidGameMat4->Initialize(device);
		materials.emplace_back(squidGameMat4);

		// 액터 생성 및 설정.
		SquidGameActor* squidGameActor2 = new SquidGameActor(device);
		squidGameActor2->SetPosition(-200.0f, 0.0f, 0.0f);
		squidGameActor2->SetStaticMesh(squidGameMesh2);
		squidGameActor2->SetMaterials(squidGameMat3, squidGameMat4);

		auto squidGameMesh3 = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh3);

		auto squidGameMat5 = new RimMaterial();
		squidGameMat5->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat5->Initialize(device);
		materials.emplace_back(squidGameMat5);

		auto squidGameMat6 = new RimMaterial();
		squidGameMat6->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat6->Initialize(device);
		materials.emplace_back(squidGameMat6);

		SquidGameActor* squidGameActor3 = new SquidGameActor(device);
		squidGameActor3->SetPosition(200.0f, 0.0f, 0.0f);
		squidGameActor3->SetStaticMesh(squidGameMesh3);
		squidGameActor3->SetMaterials(squidGameMat5, squidGameMat6);

		// 액터 생성 및 설정.
		auto squidGameMesh4 = new StaticMesh();
		ModelLoader::LoadModel(device, "PinkSoldier_v01.fbx", squidGameMesh4);

		auto squidGameMat7 = new RimNormalMappingMaterial();
		squidGameMat7->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat7->AddTexture(new Texture(L"PinkSoldier_BaseColor_1001.png"));
		squidGameMat7->AddTexture(new Texture(L"PinkSoldier_Normal_1001.png"));
		squidGameMat7->SetRimLightColor({ 1.0f, 0.0f, 1.0f });
		squidGameMat7->Initialize(device);
		materials.emplace_back(squidGameMat7);

		auto squidGameMat8 = new RimNormalMappingMaterial();
		squidGameMat8->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat8->AddTexture(new Texture(L"PinkSoldier_BaseColor_1002.png"));
		squidGameMat8->AddTexture(new Texture(L"PinkSoldier_Normal_1002.png"));
		squidGameMat7->SetRimLightColor({ 1.0f, 0.0f, 1.0f });
		squidGameMat8->Initialize(device);
		materials.emplace_back(squidGameMat8);

		SquidGameActor* squidGameActor4 = new SquidGameActor(device);
		squidGameActor4->SetPosition(300.0f, 0.0f, 0.0f);
		squidGameActor4->SetStaticMesh(squidGameMesh4);
		squidGameActor4->SetMaterials(squidGameMat7, squidGameMat8);

		// 스카이 박스.
		StaticMesh* sphereMesh = new StaticMesh();
		ModelLoader::LoadModel(device, "Sphere.FBX", sphereMesh);

		auto cubemapMaterial = new CubeMapMaterial();
		cubemapMaterial->AddTexture(new Texture(TEXT("skybox2.dds")));
		cubemapMaterial->Initialize(device);
		materials.emplace_back(cubemapMaterial);

		Actor* cubemapActor = new Actor(device, TEXT("Skybox"));
		cubemapActor->SetScale(100.0f, 100.0f, 100.0f);
		auto cubemapMeshComponent = new StaticMeshComponent();
		cubemapMeshComponent->SetStaticMesh(sphereMesh);
		cubemapMeshComponent->AddMaterial(cubemapMaterial);
		cubemapActor->AddComponent(cubemapMeshComponent);

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
		AddActor(squidGameActor2);
		AddActor(squidGameActor3);
		AddActor(squidGameActor4);
		AddActor(cubemapActor);
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