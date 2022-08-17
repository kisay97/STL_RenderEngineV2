#include "Core.h"
#include "RimMaterial.h"
#include <EngineShader/STLRimShader.h>

namespace STL
{
	RimMaterial::RimMaterial()
		: Material()
	{
		shader = new STLRimShader();
	}

	RimMaterial::~RimMaterial()
	{
	}
}