#include "RenderTargetView.h"
#include <Utility/STLException.h>
#include <cassert>

namespace STL
{
	RenderTargetView::RenderTargetView()
		: renderTargetView(nullptr)
	{
	}

	RenderTargetView::~RenderTargetView()
	{
		SafeRelease(renderTargetView);
	}
	
	void RenderTargetView::Create(IDXGISwapChain* swapChain, ID3D11Device* device)
	{
        // ����(Render, �׸���, Draw) Ÿ�� (�����) -> �츮�� �̹����� �׸� ����(�޸�).
        ID3D11Texture2D* backbuffer = nullptr;

        // �׷���ī�尡 ������ �ִ� ����� ������ ���´�.
        auto result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));

        // ���� Ȯ��.
        ThrowIfFailed(result, "Failed to get back buffer.");
		assert(backbuffer != nullptr);

        // ���� Ÿ�� ��(RenderTagetView) ����.
        result = device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);

        // ���� Ȯ��.
        ThrowIfFailed(result, "Failed to create render target.");

        // ����� ����.
        // COM.
		SafeRelease(backbuffer);
	}
	
	void RenderTargetView::Bind(ID3D11DeviceContext* context)
	{
		context->OMSetRenderTargets(1, &renderTargetView, nullptr);
	}
	
	
	void RenderTargetView::Clear(ID3D11DeviceContext* context, const float* clearColor)
	{
		context->ClearRenderTargetView(renderTargetView, clearColor);
	}
}