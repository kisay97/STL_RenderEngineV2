#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLPositionColorShader : public STLShader
    {
    public:
        STLPositionColorShader();
        ~STLPositionColorShader() = default;
    };
}