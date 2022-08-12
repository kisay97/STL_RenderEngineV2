#include "Core.h"
#include "STLDiffuseShader.h"

namespace STL
{
	STLDiffuseShader::STLDiffuseShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("DiffuseVertexShader"));
		pixelShader = PixelShader(TEXT("DiffusePixelShader"));
	}
}