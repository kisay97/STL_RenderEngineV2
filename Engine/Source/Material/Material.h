#pragma once

#include <Core/Core.h>
#include <EngineShader/STLShader.h>
#include <Renderer/Texture.h>
#include <Renderer/SamplerState.h>

namespace STL
{
	// 머티리얼 = 쉐이더 + 파라미터(텍스처, 상수 값...).
	class ENGINE_API Material
	{
	public:
		Material();
		virtual ~Material();

		virtual void Initialize(ID3D11Device* device);
		virtual void Bind(ID3D11DeviceContext* context);

		void AddTexture(Texture* const newTexture);

		ID3DBlob* GetVertexShaderBuffer()
		{
			// 쉐이더 코드가 컴파일된 후의 바이트 코드 = 쉐이더 버퍼.
			return shader->GetVertexShaderBuffer();
		}

		ID3DBlob* GetPixelShaderBuffer()
		{
			return shader->GetPixelShaderBuffer();
		}

	protected:
		uint32 index;
		STLShader* shader;
		std::vector<Texture*> textures;
		SamplerState samplerState;
	};
}