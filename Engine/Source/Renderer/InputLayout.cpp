#include "InputLayout.h"

namespace STL
{
	InputLayout::InputLayout()
		: inputLayout(nullptr)
	{
	}

	InputLayout::~InputLayout()
	{
		SafeRelease(inputLayout);
	}
	
	void InputLayout::Create(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, uint32 count, ID3DBlob* vertexShaderBuffer)
	{
		auto result = device->CreateInputLayout(
			layout, count, 
			vertexShaderBuffer->GetBufferPointer(), 
			vertexShaderBuffer->GetBufferSize(), 
			&inputLayout
		);

		ThrowIfFailed(result, "Failed to create Input Layout.");
	}

	void InputLayout::Create(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
	{
		ID3D11ShaderReflection* vertexShaderReflection;
		HRESULT hr = D3DReflect(
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			IID_ID3D11ShaderReflection,
			reinterpret_cast<void**>(&vertexShaderReflection)
		);

		ThrowIfFailed(hr, "Failed to get info with shader reflection.");

		D3D11_SHADER_DESC desc = { };
		vertexShaderReflection->GetDesc(&desc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
		for (uint32 ix = 0; ix < desc.InputParameters; ++ix)
		{
			D3D11_SIGNATURE_PARAMETER_DESC parameterDesc = { };
			vertexShaderReflection->GetInputParameterDesc(ix, &parameterDesc);

			D3D11_INPUT_ELEMENT_DESC elementDesc = { 0 };
			elementDesc.SemanticName = parameterDesc.SemanticName;
			elementDesc.SemanticIndex = parameterDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			elementDesc.InstanceDataStepRate = 0;

			// Get Format.
			if (parameterDesc.Mask == 1)
			{
				if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32_UINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32_SINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
				}
			}
			else if (parameterDesc.Mask <= 3)
			{
				if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
				}
			}
			else if (parameterDesc.Mask <= 7)
			{
				if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				}
			}
			else if (parameterDesc.Mask <= 15)
			{
				if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				}
				else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				}
			}

			// Save element desc.
			layout.emplace_back(elementDesc);
		}

		hr = device->CreateInputLayout(
			layout.data(),
			static_cast<uint32>(layout.size()),
			vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),
			&inputLayout
		);

		ThrowIfFailed(hr, "Failed to create input layout.");
	}
	
	void InputLayout::Bind(ID3D11DeviceContext* context)
	{
		context->IASetInputLayout(inputLayout);
	}
}