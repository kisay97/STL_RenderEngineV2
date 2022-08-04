#pragma once

#include <Core/Core.h>
#include "Buffer.h"

namespace STL
{
	// 상수 버퍼.
	// 쉐이더에 전달할 데이터 중에 입력 구조체 외에 다른 일반 데이터를 전달할 때 사용.
	class ENGINE_API ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer();
		ConstantBuffer(void* data, size_t count, uint32 byteWidth);
		~ConstantBuffer();

		virtual void Create(ID3D11Device * device) override;

		// 데이터를 업데이트할 때 사용.
		void Update(ID3D11DeviceContext* context, void* data);
		// Draw 콜 하기 전에 상수 버퍼를 파이프라인에 연결할 때 사용.
		void Bind(ID3D11DeviceContext* context, uint32 index);

	private:
		virtual void Bind(ID3D11DeviceContext* context) override;
	};
}