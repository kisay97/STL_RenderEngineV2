#include <Core/Core.h>
#include "Game.h"

using STL::Game;

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    try 
    {
        std::unique_ptr<Game> game = std::make_unique<Game>(
            hInstance, 1600, 900, L"STL Render Engine"
        );
        game->Run();
    }
    catch (std::exception ex)
    {
        return -1;
    }
    return 0;
}