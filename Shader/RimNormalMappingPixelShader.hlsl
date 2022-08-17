#include "Common.hlsl"

struct PSInput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
    float3 binormal : TEXCOORD2;
    float3 tangent : TEXCOORD3;
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

struct Rim
{
    float3 color;
    float constant;
};

cbuffer RimProperties : register(b2)
{
    Rim rim;
};

// 텍스처.
Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// 샘플링 (표본 추출, 색상 추출).
    float4 diffuseMapColor = diffuseMap.Sample(mapSampler, input.texCoord);
	
    float4 specularMapColor = specularMap.Sample(mapSampler, input.texCoord);
    
    // 노멀맵 추출.
    float4 tangentNormal = normalMap.Sample(mapSampler, input.texCoord);
    tangentNormal = tangentNormal * 2 - 1;
    
    // 탄젠트 공간 -> 월드 공간 변환 행렬 구하기(TBN)
    float3x3 TBN = float3x3(
        normalize(input.tangent),
        normalize(input.binormal),
        normalize(input.normal)
    );
    
	// 조명 방향.
    float3 lightDirection = normalize(-light.position);
	
	// 월드 노멀.
    //float3 worldNormal = normalize(input.normal);
    float3 worldNormal = mul(tangentNormal.xyz, TBN);
	
	// 디퓨즈.
    float diffusePower = ComputeLambert(worldNormal, lightDirection);
	
	// 조명 밝기에 조명 색상 적용.
    float4 diffuse = float4(light.color * diffusePower, 1);

	// 스페큘러 - 퐁.
    input.cameraDirection = normalize(input.cameraDirection);
    float specularPower = ComputePhong(
    diffusePower, worldNormal, lightDirection, input.cameraDirection, material.shiness);
        
    float4 specular = float4(light.color * specularPower, 1);
    
    // 림 라이트.
    float3 vertexNormal = normalize(input.normal);
    float4 rimLight = ComputeRimPower(rim.color, vertexNormal, input.cameraDirection, rim.constant);
	
    // 최종 색상 계산.
    float4 finalColor
    = (diffuse * diffuseMapColor)
    + (specular * specularMapColor)
    + rimLight;
    return finalColor;
}