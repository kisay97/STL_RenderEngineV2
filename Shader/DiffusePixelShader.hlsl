struct PSInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

// ��� ���� (����Ʈ).
cbuffer Light : register(b0)
{
	float3 lightPosition;
	float pad1;
	float3 lightColor;
	float pad2;
}

// �ؽ�ó.
Texture2D diffuseMap : register(t0);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// ���ø� (���� ����).
	float4 mapColor = diffuseMap.Sample(mapSampler, input.texCoord);

	// ���� ����.
	float3 lightDirection = normalize(-lightPosition);

	// ���� ���.
	float3 worldNormal = normalize(input.normal);

	// ��ǻ�� - ����Ʈ(Lambert).
	// ���� ��� ��� - ��ְ� ���� ���� ���Ϳ��� �������� cos(theta) ���.
	float diffusePower = dot(worldNormal, -lightDirection);
	// ��������Ʈ
	diffusePower = pow(diffusePower * 0.5f + 0.5f, 2);
	// ���� ��⿡ ���� ���� ����.
	float4 diffuse = float4(lightColor * diffusePower, 1);

	// ���� ���� ���.
	float4 finalColor = diffuse * mapColor;
	
	return finalColor;
}