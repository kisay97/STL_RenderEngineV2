#include "Core.h"
#include "STLRimNormalMappingShader.h"

namespace STL
{
	STLRimNormalMappingShader::STLRimNormalMappingShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("RimNormalMappingVertexShader"));
		pixelShader = PixelShader(TEXT("RimNormalMappingPixelShader"));
	}
}