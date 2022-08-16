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

// �ؽ�ó.
Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// ���ø� (ǥ�� ����, ���� ����).
	float4 diffuseMapColor = diffuseMap.Sample(mapSampler, input.texCoord);
	
    float4 specularMapColor = specularMap.Sample(mapSampler, input.texCoord);
    
	// ���� ����.
    float3 lightDirection = normalize(-light.position);
	
	// ���� ���.
    float3 worldNormal = normalize(input.normal);
	
	// ��ǻ��.
    float diffusePower = ComputeHalfLambert(worldNormal, lightDirection);
	
	// ���� ��⿡ ���� ���� ����.
    float4 diffuse = float4(light.color * diffusePower, 1);

    // ī�� ���̴�(Cartoon) - ��(Cell) ���̵�
    float toonStep = 3;
    //diffuse = ceil(diffuse * toonStep) / toonStep;
    float4 white = float4(1, 1, 1, 1);
    float4 gray = float4(0.3, 0.3, 0.3, 1);
    float4 darkGray = float4(0.1, 0.1, 0.1, 1);
    if (diffusePower > 0)
    {
        diffuse = darkGray;
    }
    if (diffusePower > 0.4)
    {
        diffuse = gray;
    }
    if (diffusePower > 0.8)
    {
        diffuse = white;
    }
    diffuse = diffuse * diffuseMapColor;

	// ����ŧ�� - ��.
    input.cameraDirection = normalize(input.cameraDirection);
    //float specularPower = ComputePhong(
        //diffusePower, worldNormal, lightDirection, input.cameraDirection, material.shiness);
    float specularPower = ComputeBlinnPhong(
        diffusePower, worldNormal, lightDirection, input.cameraDirection, material.shiness);

    float4 specular = float4(light.color * specularPower, 1);
    //specular = ceil(specular * toonStep) / toonStep;
	
    // ���� ���� ���.
    float4 finalColor = (diffuse * diffuseMapColor) + (specular * specularMapColor);
    return finalColor;
}