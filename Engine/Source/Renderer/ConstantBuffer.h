#pragma once

#include <Core/Core.h>
#include "Buffer.h"

namespace STL
{
	// ��� ����.
	// ���̴��� ������ ������ �߿� �Է� ����ü �ܿ� �ٸ� �Ϲ� �����͸� ������ �� ���.
	class ENGINE_API ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer();
		ConstantBuffer(void* data, size_t count, uint32 byteWidth);
		~ConstantBuffer();

		virtual void Create(ID3D11Device * device) override;

		// �����͸� ������Ʈ�� �� ���.
		void Update(ID3D11DeviceContext* context, void* data);
		// Draw �� �ϱ� ���� ��� ���۸� ���������ο� ������ �� ���.
		void Bind(ID3D11DeviceContext* context, uint32 index);

	private:
		virtual void Bind(ID3D11DeviceContext* context) override;
	};
}