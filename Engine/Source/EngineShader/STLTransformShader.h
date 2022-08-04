#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLTransformShader : public STLShader
    {
    public:
        STLTransformShader();
        ~STLTransformShader() = default;
    };
}