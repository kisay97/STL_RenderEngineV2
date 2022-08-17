#include "Core.h"
#include "STLRimShader.h"

namespace STL
{
	STLRimShader::STLRimShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("RimVertexShader"));
		pixelShader = PixelShader(TEXT("RimPixelShader"));
	}
}