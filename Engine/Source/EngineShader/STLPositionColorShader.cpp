#include "STLPositionColorShader.h"

namespace STL
{
	STLPositionColorShader::STLPositionColorShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("PositionColorVertexShader"));
		pixelShader = PixelShader(TEXT("PositionColorPixelShader"));
	}
}