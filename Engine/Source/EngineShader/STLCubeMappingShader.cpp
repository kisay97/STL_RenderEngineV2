#include "Core.h"
#include "STLCubeMappingShader.h"

namespace STL
{
	STLCubeMappingShader::STLCubeMappingShader()
		: STLShader()
	{
		vertexShader = VertexShader(TEXT("CubeMapVertexShader"));
		pixelShader = PixelShader(TEXT("CubeMapPixelShader"));		
	}
	
	void STLCubeMappingShader::Initialize(ID3D11Device* device)
	{
		rasterizerState.SetCullMode(D3D11_CULL_NONE);
		STLShader::Initialize(device);
	}
}