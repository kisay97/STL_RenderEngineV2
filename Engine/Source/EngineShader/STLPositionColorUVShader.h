#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLPositionColorUVShader : public STLShader
    {
    public:
        STLPositionColorUVShader();
        ~STLPositionColorUVShader() = default;
    };
}