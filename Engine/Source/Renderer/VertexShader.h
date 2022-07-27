#pragma once

#include <Core/Core.h>
#include "Shader.h"

namespace STL
{
	class ENGINE_API VertexShader : public Shader
	{
	public:
		VertexShader();
		VertexShader(const std::wstring & filename);
		VertexShader(const std::wstring & filename,
			const std::string & entry, const std::string & profile);
		~VertexShader();

		virtual void Initialize(ID3D11Device * device) override;
		virtual void Bind(ID3D11DeviceContext * context) override;

		ID3D11VertexShader* Get() { return vertexShader; }
		ID3D11VertexShader** GetAddressOf() { return &vertexShader; }

	protected:

		virtual void Compile(ID3D11Device * device) override;
		virtual void Create(ID3D11Device * device) override;

	private:
		ID3D11VertexShader* vertexShader;
	};
}

