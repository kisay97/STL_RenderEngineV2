#include "STLPositionColorUVShader.h"

namespace STL
{
	STLPositionColorUVShader::STLPositionColorUVShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("PositionColorUVVertexShader"));
		pixelShader = PixelShader(TEXT("PositionColorUVPixelShader"));
	}
}