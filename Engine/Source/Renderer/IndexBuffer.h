#pragma once

#include <Core/Core.h>
#include "Buffer.h"

namespace STL
{
	class ENGINE_API IndexBuffer : public Buffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(void* data, size_t count, uint32 byteWidth = sizeof(uint32));
		~IndexBuffer() = default;

		virtual void Create(ID3D11Device* device) override;
		virtual void Bind(ID3D11DeviceContext* context) override;
	};
}