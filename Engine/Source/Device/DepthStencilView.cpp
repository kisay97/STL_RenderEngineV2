#include "Core.h"
#include "DepthStencilView.h"
#include <Utility/STLException.h>

namespace STL
{
	DepthStencilView::DepthStencilView()
		: depthStencilView(nullptr)
	{
	}

	DepthStencilView::~DepthStencilView()
	{
		SafeRelease(depthStencilView);
	}
	
	void DepthStencilView::Create(ID3D11Device* device, 
		uint32 width, uint32 height, bool use4xaa, uint32 numQualityLevels)
	{
		// ���� ���ٽ� ���� ����.
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1; // �Ӹ� ����.
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		// D3D11_USAGE_DEFAULT -> �����Ͱ� ���� �ٲ��� ���� �� �ַ� ���.
		// D3D11_USAGE_DYNAMIC -> �����Ͱ� ���� �ٲ� �� �ַ� ��� (��: �� ������ ����).
		if (use4xaa)
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = numQualityLevels - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}

		// ���� ���ٽ� �� ����.
		ID3D11Texture2D* depthStencilBuffer = nullptr;
		auto result = device->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&depthStencilBuffer
		);

		ThrowIfFailed(result, "Failed to create depth stencil buffer");

		// ���� ���ٽ� �� ����.
		assert(depthStencilBuffer);
		result = device->CreateDepthStencilView(
			depthStencilBuffer,
			nullptr,
			&depthStencilView
		);

		SafeRelease(depthStencilBuffer);
		ThrowIfFailed(result, "Failed to create depth stencil view");
	}
	
	void DepthStencilView::Clear(ID3D11DeviceContext* context, 
		uint32 clearFlags, float depth, uint8 stencil)
	{
		context->ClearDepthStencilView(
			depthStencilView, clearFlags, depth, stencil
		);
	}
}