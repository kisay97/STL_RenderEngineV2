#include "Game.h"
#include <Renderer/VertexDeclaration.h>
#include <Utility/TextureLoader.h>
#include <Utility/STLException.h>
#include <Math/MathHelper.h>

#include <Device/KeyboardInput.h>

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
		
		// ���� �ʱ�ȭ
		mainLevel.Initialize(device, this);
	}

	void Game::Update(float deltaTime)
	{
		// ���� ������Ʈ.
		auto context = deviceManager->GetContext();
		mainLevel.Update(context, deltaTime);
	}

	void Game::RenderScene()
	{
		auto context = deviceManager->GetContext();

		mainLevel.Bind(context);
		mainLevel.Draw(context);
	}
	void Game::ProcessInput()
	{
		Application::ProcessInput();
		
		if (keyboard->IsKeyDown(Keys::Escape))
		{
			if (MessageBox(nullptr, L"���� �Ͻðڽ��ϱ�?", L"����", MB_YESNO) == IDYES)
			{
				DestroyWindow(mainWindow->Handle());
			}
		}
	}
}