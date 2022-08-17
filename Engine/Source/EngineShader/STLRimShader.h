#pragma once

#include <Core/Core.h>
#include "STLShader.h"
#include <Renderer/RasterizerState.h>

namespace STL
{
    class ENGINE_API STLRimShader : public STLShader
    {
    public:
        STLRimShader();
        ~STLRimShader() = default;
    };
}