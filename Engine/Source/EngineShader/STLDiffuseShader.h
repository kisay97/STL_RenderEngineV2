#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLDiffuseShader : public STLShader
    {
    public:
        STLDiffuseShader();
        ~STLDiffuseShader() = default;
    };
}