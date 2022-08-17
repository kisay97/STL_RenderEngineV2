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

// ��� ���� (����Ʈ).
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

// �ؽ�ó.
Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// ���ø� (ǥ�� ����, ���� ����).
    float4 diffuseMapColor = diffuseMap.Sample(mapSampler, input.texCoord);
	
    float4 specularMapColor = specularMap.Sample(mapSampler, input.texCoord);
    
    // ��ָ� ����.
    float4 tangentNormal = normalMap.Sample(mapSampler, input.texCoord);
    tangentNormal = tangentNormal * 2 - 1;
    
    // ź��Ʈ ���� -> ���� ���� ��ȯ ��� ���ϱ�(TBN)
    float3x3 TBN = float3x3(
        normalize(input.tangent),
        normalize(input.binormal),
        normalize(input.normal)
    );
    
	// ���� ����.
    float3 lightDirection = normalize(-light.position);
	
	// ���� ���.
    //float3 worldNormal = normalize(input.normal);
    float3 worldNormal = mul(tangentNormal.xyz, TBN);
	
	// ��ǻ��.
    float diffusePower = ComputeLambert(worldNormal, lightDirection);
	
	// ���� ��⿡ ���� ���� ����.
    float4 diffuse = float4(light.color * diffusePower, 1);

	// ����ŧ�� - ��.
    input.cameraDirection = normalize(input.cameraDirection);
    float specularPower = ComputePhong(
    diffusePower, worldNormal, lightDirection, input.cameraDirection, material.shiness);
        
    float4 specular = float4(light.color * specularPower, 1);
    
    // �� ����Ʈ.
    float3 vertexNormal = normalize(input.normal);
    float4 rimLight = ComputeRimPower(rim.color, vertexNormal, input.cameraDirection, rim.constant);
	
    // ���� ���� ���.
    float4 finalColor
    = (diffuse * diffuseMapColor)
    + (specular * specularMapColor)
    + rimLight;
    return finalColor;
}