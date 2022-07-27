#include "VertexBuffer.h"
#include <Utility/STLException.h>

namespace STL
{
	VertexBuffer::VertexBuffer(void* data, size_t count, uint32 byteWidth)
		: Buffer(data, count, byteWidth)
	{
	}

	void VertexBuffer::Create(ID3D11Device* device)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = byteWidth * static_cast<uint32>(count);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = data;

		auto result = device->CreateBuffer(&desc, &vertexData, &buffer);
		ThrowIfFailed(result, "Failed to create vertex buffer.");
	}
	
	void VertexBuffer::Bind(ID3D11DeviceContext* context)
	{
		static const uint32 stride = byteWidth;
		static const uint32 offset = 0u;

		context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}