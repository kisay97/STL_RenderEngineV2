#include "Core.h"
#include "IndexBuffer.h"
#include <Utility/STLException.h>

namespace STL
{
	IndexBuffer::IndexBuffer(void* data, size_t count, uint32 byteWidth)
		: Buffer(data, count, byteWidth)
	{
	}

	void IndexBuffer::Create(ID3D11Device* device)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = byteWidth * static_cast<uint32>(count);
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = data;

		auto result = device->CreateBuffer(&desc, &indexData, &buffer);
		ThrowIfFailed(result, "Failed to create index buffer.");
	}

	void IndexBuffer::Bind(ID3D11DeviceContext* context)
	{
		context->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0u);
	}
}