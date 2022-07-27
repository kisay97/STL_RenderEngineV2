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
		virtual void Initialize() override;

	private:
		uint32 vertexByteWidth;
		uint32 vertexCount;
	};
}