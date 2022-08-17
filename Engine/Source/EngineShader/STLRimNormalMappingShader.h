#pragma once

#include <Core/Core.h>
#include "STLShader.h"

namespace STL
{
    class ENGINE_API STLRimNormalMappingShader : public STLShader
    {
    public:
        STLRimNormalMappingShader();
        ~STLRimNormalMappingShader() = default;
    };
}