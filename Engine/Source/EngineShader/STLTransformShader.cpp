#include "Core.h"
#include "STLTransformShader.h"

namespace STL
{
	STLTransformShader::STLTransformShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("TransformVertexShader"));
		pixelShader = PixelShader(TEXT("TransformPixelShader"));
	}
}