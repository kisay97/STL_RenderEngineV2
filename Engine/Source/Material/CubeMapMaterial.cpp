#include "Core.h"
#include "CubeMapMaterial.h"
#include <EngineShader/STLCubeMappingShader.h>

namespace STL
{
	CubeMapMaterial::CubeMapMaterial()
		: Material()
	{
		shader = new STLCubeMappingShader();
	}

	CubeMapMaterial::~CubeMapMaterial()
	{
	}
}