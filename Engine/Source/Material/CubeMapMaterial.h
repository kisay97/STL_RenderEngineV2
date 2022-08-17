#pragma once

#include <Core/Core.h>
#include "Material.h"

namespace STL
{
	class ENGINE_API CubeMapMaterial : public Material
	{
	public:
		CubeMapMaterial();
		~CubeMapMaterial();
	};
}