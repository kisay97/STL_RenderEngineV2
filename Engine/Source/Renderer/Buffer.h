#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API Buffer
	{
	public:
		Buffer() = default;
		Buffer(void* data, size_t count, uint32 byteWidth);
		virtual ~Buffer();

		// ���� ���� �Լ� -> ������ �ڽ� Ŭ��������
		// ���� ���ϸ� ���� �߻�.
		virtual void Create(ID3D11Device* device) = 0;
		virtual void Bind(ID3D11DeviceContext* context) = 0;

		virtual uint32 Count() { return static_cast<uint32>(count); }
		virtual uint32 ByteWidth() { return byteWidth; }

		virtual ID3D11Buffer* Get() { return buffer; }
		virtual ID3D11Buffer** GetAddressOf() { return &buffer; }

	protected:
		void* data;
		size_t count;
		uint32 byteWidth;
		ID3D11Buffer* buffer;
	};
}