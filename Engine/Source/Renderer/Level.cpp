#include "Core.h"
#include "Level.h"
#include <Component/Actor.h>
#include <Component/CameraComponent.h>
#include <Component/LightComponent.h>

namespace STL
{
	Level::Level()
		: mainCamera(nullptr), mainLight(nullptr)
	{
	}

	Level::~Level()
	{
		for (auto actor : actors)
		{
			if (actor != nullptr)
			{
				delete actor;
				actor = nullptr;
			}
		}
	}

	void Level::AddActor(Actor* actor)
	{
		// 카메라 액터 추가.
		auto camera = actor->GetComponent<CameraComponent>();
		if (camera != nullptr)
		{
			mainCamera = actor;
			return;
		}

		auto light = actor->GetComponent<LightComponent>();
		if (light != nullptr)
		{
			mainLight = actor;
			return;
		}

		actors.emplace_back(actor);
	}

	void Level::Initialize(ID3D11Device* device, Application* engine)
	{
		// 카메라 초기화.
		mainCamera->Create(device);

		if (mainLight != nullptr)
		{
			// 라이트 초기화.
			mainLight->Create(device);
		}

		// 액터가 가진 모든 컴포넌트 초기화.
		for (auto actor : actors)
		{
			actor->Create(device);
		}
	}

	void Level::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// 카메라 업데이트.
		mainCamera->Update(context, deltaTime);

		if (mainLight != nullptr)
		{
			// 라이트 업데이트.
			mainLight->Update(context, deltaTime);
		}

		// 액터가 가진 모든 컴포넌트 업데이트.
		for (auto actor : actors)
		{
			actor->Update(context, deltaTime);
		}
	}

	void Level::Bind(ID3D11DeviceContext* context)
	{
		// 카메라 바인딩.
		mainCamera->Bind(context);

		if (mainLight != nullptr)
		{
			// 라이트 바인딩.
			mainLight->Bind(context);
		}

		for (auto actor : actors)
		{
			actor->Bind(context);
		}
	}

	void Level::Draw(ID3D11DeviceContext* context)
	{
		// 카메라 바인딩.
		mainCamera->Bind(context);

		if (mainLight != nullptr)
		{
			// 라이트 바인딩.
			mainLight->Bind(context);
		}

		for (auto actor : actors)
		{
			actor->Draw(context);
		}
	}
}