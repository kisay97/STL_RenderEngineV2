#include "Common.hlsl"

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
Texture2D specularMap : register(t1);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// 샘플링 (표본 추출, 색상 추출).
	float4 diffuseMapColor = diffuseMap.Sample(mapSampler, input.texCoord);
	
    float4 specularMapColor = specularMap.Sample(mapSampler, input.texCoord);
    
	// 조명 방향.
    float3 lightDirection = normalize(-light.position);
	
	// 월드 노멀.
    float3 worldNormal = normalize(input.normal);
	
	// 디퓨즈.
    float diffusePower = ComputeHalfLambert(worldNormal, lightDirection);
	
	// 조명 밝기에 조명 색상 적용.
    float4 diffuse = float4(light.color * diffusePower, 1);

	// 스페큘러 - 퐁.
    input.cameraDirection = normalize(input.cameraDirection);
    //float specularPower = ComputePhong(
        //diffusePower, worldNormal, lightDirection, input.cameraDirection, material.shiness);
    float specularPower = ComputeBlinnPhong(
        diffusePower, worldNormal, lightDirection, input.cameraDirection, material.shiness);

    float4 specular = float4(light.color * specularPower, 1);
	
    // 최종 색상 계산.
    float4 finalColor = (diffuse * diffuseMapColor) + (specular * specularMapColor);
    return finalColor;
}