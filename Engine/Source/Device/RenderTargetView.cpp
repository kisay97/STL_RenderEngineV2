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
        // 렌더(Render, 그린다, Draw) 타겟 (백버퍼) -> 우리가 이미지를 그릴 버퍼(메모리).
        ID3D11Texture2D* backbuffer = nullptr;

        // 그래픽카드가 가지고 있는 백버퍼 정보를 얻어온다.
        auto result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));

        // 오류 확인.
        ThrowIfFailed(result, "Failed to get back buffer.");
		assert(backbuffer != nullptr);

        // 렌더 타켓 뷰(RenderTagetView) 생성.
        result = device->CreateRenderTargetView(backbuffer, nullptr, &renderTargetView);

        // 오류 확인.
        ThrowIfFailed(result, "Failed to create render target.");

        // 백버퍼 해제.
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