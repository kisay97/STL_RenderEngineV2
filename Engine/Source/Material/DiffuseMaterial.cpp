#include "Core.h"
#include "DiffuseMaterial.h"
#include <EngineShader/STLDiffuseShader.h>

namespace STL
{
	DiffuseMaterial::DiffuseMaterial()
		: Material()
	{
		shader = new STLDiffuseShader();
	}

	DiffuseMaterial::~DiffuseMaterial()
	{
	}
}