#pragma once

#include <Core/Core.h>
#include "Shader.h"

namespace STL
{
	class ENGINE_API PixelShader : public Shader
	{
	public:
		PixelShader();
		PixelShader(const std::wstring& filename);
		PixelShader(const std::wstring& filename,
			const std::string& entry, const std::string& profile);
		~PixelShader();

		virtual void Initialize(ID3D11Device* device) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		ID3D11PixelShader* Get() { return pixelShader; }
		ID3D11PixelShader** GetAddressOf() { return &pixelShader; }

	protected:

		virtual void Compile(ID3D11Device* device) override;
		virtual void Create(ID3D11Device* device) override;

	private:
		ID3D11PixelShader* pixelShader;
	};
}

