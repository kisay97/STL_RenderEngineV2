#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLNormalMappingShader : public STLShader
    {
    public:
        STLNormalMappingShader();
        ~STLNormalMappingShader() = default;
    };
}