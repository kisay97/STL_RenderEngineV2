// ���� ���̴� �Է�.
struct VSInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// ���� ���̴� ��� -> �ȼ� ���̴��� �Է�.
struct VSOutput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// ��� ����.
cbuffer Transform : register(b0)
{
	// ���
	// float4x4
	matrix world;
};

VSOutput main(VSInput input)
{
	VSOutput output;
	output.position = mul(float4(input.position, 1), world);
	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}