#pragma once

#include <Core/Core.h>
#include "STLShader.h"
#include <Renderer/RasterizerState.h>

namespace STL
{
    class ENGINE_API STLCubeMappingShader : public STLShader
    {
    public:
        STLCubeMappingShader();
        ~STLCubeMappingShader() = default;

        virtual void Initialize(ID3D11Device* device) override;
    };
}