#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLDiffuseSpecularShader : public STLShader
    {
    public:
        STLDiffuseSpecularShader();
        ~STLDiffuseSpecularShader() = default;

        virtual void Initialize(ID3D11Device* device) override;
        virtual void Bind(ID3D11DeviceContext* deviceContext) override;
    };
}