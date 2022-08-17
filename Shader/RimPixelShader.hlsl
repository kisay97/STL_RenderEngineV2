#include "Common.hlsl"

// 픽셀 쉐이더의 입력.
struct PSInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
};

struct Light
{
    float3 position;
    float pad1;
    float3 color;
    float pad2;
};

// 상수 버퍼 (라이트).
cbuffer LightProperties : register(b0)
{
    Light light;
};

struct Material
{
    float shiness;
    float3 pad;
};

cbuffer MaterialProperties : register(b1)
{
    Material material;
};

// 텍스처.
Texture2D diffuseMap : register(t0);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
    // 텍스처 색상 추출.
    float4 diffuseMapColor = diffuseMap.Sample(mapSampler, input.texCoord);
    
    float3 cameraDirection = normalize(input.cameraDirection);
    float3 worldNormal = normalize(input.normal);
    float3 rimColor = float3(1.0f, 1.0f, 1.0f);
    float rimConstant = 4.0f;
    
    return ComputeRimPower(rimColor, worldNormal, cameraDirection, rimConstant);
}