#pragma once

#include <Core/Core.h>
#include <EngineShader/STLShader.h>
#include <Renderer/Texture.h>
#include <Renderer/SamplerState.h>

namespace STL
{
	// ��Ƽ���� = ���̴� + �Ķ����(�ؽ�ó, ��� ��...).
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
			// ���̴� �ڵ尡 �����ϵ� ���� ����Ʈ �ڵ� = ���̴� ����.
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