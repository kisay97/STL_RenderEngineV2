#include "Core.h"
#include "TransformMaterial.h"
#include <EngineShader/STLTransformShader.h>

namespace STL
{
	TransformMaterial::TransformMaterial()
		: Material()
	{
		shader = new STLTransformShader();
	}

	TransformMaterial::~TransformMaterial()
	{
	}
}