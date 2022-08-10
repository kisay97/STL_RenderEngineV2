#include "Core.h"
#include "Level.h"
#include <Component/Actor.h>
#include <Component/CameraComponent.h>

namespace STL
{
	Level::Level()
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
		// ī�޶� ���� �߰�.
		auto camera = actor->GetComponent<CameraComponent>();
		if (camera != nullptr)
		{
			mainCamera = actor;
			return;
		}

		actors.emplace_back(actor);
	}

	void Level::Initialize(ID3D11Device* device, Application* engine)
	{
		// ī�޶� �ʱ�ȭ.
		mainCamera->Create(device);

		// ���Ͱ� ���� ��� ������Ʈ �ʱ�ȭ.
		for (auto actor : actors)
		{
			actor->Create(device);
		}
	}

	void Level::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// ī�޶� ������Ʈ.
		mainCamera->Update(context, deltaTime);

		// ���Ͱ� ���� ��� ������Ʈ ������Ʈ.
		for (auto actor : actors)
		{
			actor->Update(context, deltaTime);
		}
	}

	void Level::Bind(ID3D11DeviceContext* context)
	{
		// ī�޶� ���ε�
		mainCamera->Bind(context);

		for (auto actor : actors)
		{
			actor->Bind(context);
		}
	}

	void Level::Draw(ID3D11DeviceContext* context)
	{
		// ī�޶� ���ε�(ī�޶� �Ⱥ����� �׸��� ������, �׸��� ���� ���ε��� �������)
		mainCamera->Bind(context);

		for (auto actor : actors)
		{
			actor->Draw(context);
		}
	}
}