#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLDefaultShader : public STLShader
    {
    public:
        STLDefaultShader();
        ~STLDefaultShader() = default;
    };
}