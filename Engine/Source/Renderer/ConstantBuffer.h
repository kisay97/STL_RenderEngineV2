#pragma once

#include <Core/Core.h>
#include "Buffer.h"

namespace STL
{
	// 열거형 - 쉐이더 단계 지정 용도. (어떤 상수 버퍼는 버텍스 쉐이더에서만 쓰고, 어떤 상수 버퍼는 픽셀 쉐이더에서만 쓰고 싶을 수 있으니까)
	enum class BindShaderTarget
	{
		VertexShader = 0,
		PixelShader
	};

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

		void SetBindShaderTarget(BindShaderTarget bindShaderTarget);

	private:
		virtual void Bind(ID3D11DeviceContext* context) override;

		BindShaderTarget bindShaderTarget;
	};
}