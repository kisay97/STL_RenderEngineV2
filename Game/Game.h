#pragma once

#include <Core/Core.h>
#include <Core/Application.h>

namespace STL 
{
	class Game : public Application
	{
	public:
		Game(
			HINSTANCE hInstance,
			uint32 width,
			uint32 height,
			const std::wstring& title
		);

		virtual ~Game();
	};
}