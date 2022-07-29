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

VSOutput main(VSInput input)
{
	VSOutput output;
	output.position = float4(input.position, 1);
	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}