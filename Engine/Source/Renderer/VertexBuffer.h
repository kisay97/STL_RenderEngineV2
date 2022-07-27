#pragma once

#include <Core/Core.h>
#include "Buffer.h"

namespace STL
{
	class ENGINE_API VertexBuffer : public Buffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(void* data, size_t count, uint32 byteWidth);
		~VertexBuffer() = default;

		virtual void Create(ID3D11Device * device) override;
		virtual void Bind(ID3D11DeviceContext * context) override;
	};
}