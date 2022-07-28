#include "STLDefaultShader.h"

namespace STL
{
	STLDefaultShader::STLDefaultShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("VertexShader"));
		pixelShader = PixelShader(TEXT("PixelShader"));
	}
}