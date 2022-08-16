#include "Core.h"
#include "STLNormalMappingShader.h"

namespace STL
{
	STLNormalMappingShader::STLNormalMappingShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("NormalMappingVertexShader"));
		pixelShader = PixelShader(TEXT("NormalMappingPixelShader"));
	}
}