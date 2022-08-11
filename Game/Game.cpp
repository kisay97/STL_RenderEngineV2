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
		// 로드한 텍스처 리소스 해제.
		TextureLoader::Release();
	}

	void Game::Initialize()
	{
		Application::Initialize();

		// 장치 참조 저장.
		auto device = deviceManager->GetDevice();
		
		// 레벨 초기화
		mainLevel.Initialize(device, this);
	}

	void Game::Update(float deltaTime)
	{
		// 레벨 업데이트.
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
			if (MessageBox(nullptr, L"종료 하시겠습니까?", L"종료", MB_YESNO) == IDYES)
			{
				DestroyWindow(mainWindow->Handle());
			}
		}
	}
}