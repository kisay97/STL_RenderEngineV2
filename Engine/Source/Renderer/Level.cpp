#include "Core.h"
#include "Level.h"
#include <Component/Actor.h>

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
		actors.emplace_back(actor);
	}

	void Level::Initialize(ID3D11Device* device)
	{
	}

	void Level::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		for (auto actor : actors)
		{
			actor->Update(context, deltaTime);
		}
	}

	void Level::Bind(ID3D11DeviceContext* context)
	{
		for (auto actor : actors)
		{
			actor->Bind(context);
		}
	}

	void Level::Draw(ID3D11DeviceContext* context)
	{
		for (auto actor : actors)
		{
			actor->Draw(context);
		}
	}
}