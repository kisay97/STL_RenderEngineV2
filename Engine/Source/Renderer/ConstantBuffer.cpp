#include "Core.h"
#include "ConstantBuffer.h"
#include <Utility/STLException.h>

namespace STL
{
	ConstantBuffer::ConstantBuffer()
		: Buffer(), bindShaderTarget(BindShaderTarget::VertexShader)
	{
	}

	ConstantBuffer::ConstantBuffer(void* data, size_t count, uint32 byteWidth)
		: Buffer(data, count, byteWidth), bindShaderTarget(BindShaderTarget::VertexShader)
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	void ConstantBuffer::Create(ID3D11Device* device)
	{
		// ���� ����.
		// ���� ��ũ���� ����ü �ۼ�
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = byteWidth;
		desc.Usage = D3D11_USAGE_DYNAMIC; //�뵵. ���� �ٲ� �����ʹ� ���̳���
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // ��� ����
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //cpu���� ���� �۾�
		
		// ���긮�ҽ� ������ �ۼ�.
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = data;

		// ���� ����.
		auto result = device->CreateBuffer(&desc, &bufferData, &buffer);
		ThrowIfFailed(result, "Failed to create constant buffer");
	}

	void ConstantBuffer::Update(ID3D11DeviceContext* context, void* data)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource = {};
		context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource); //���� �����ؼ� ���� ������ ��� �� mappedResource�� �����Ͽ� ���
		memcpy(mappedResource.pData, data, byteWidth); // == mappedResource.pData = data;
		context->Unmap(buffer, 0); //��ʽ� ������Ʈ ��.
	}

	void ConstantBuffer::Bind(ID3D11DeviceContext* context, uint32 index)
	{
		if (bindShaderTarget == BindShaderTarget::VertexShader) 
		{
			context->VSSetConstantBuffers(index, 1, &buffer);
		}
		else if (bindShaderTarget == BindShaderTarget::PixelShader)
		{
			context->PSSetConstantBuffers(index, 1, &buffer);
		}
	}

	void ConstantBuffer::SetBindShaderTarget(BindShaderTarget bindShaderTarget)
	{
		this->bindShaderTarget = bindShaderTarget;
	}

	void ConstantBuffer::Bind(ID3D11DeviceContext* context)
	{
		Bind(context, 0);
	}
}