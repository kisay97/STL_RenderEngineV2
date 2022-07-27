#include "Game.h"

namespace STL 
{
	Game::Game(HINSTANCE hInstance, uint32 width, uint32 height, const std::wstring& title)
		: Application(hInstance, width, height, title), vertexByteWidth(0), vertexCount(0)
	{
	}

	Game::~Game()
	{
	}

	void Game::Initialize()
	{
		Application::Initialize();
	}
}