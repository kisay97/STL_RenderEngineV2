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

// ī�޶��� �����/�������/��ġ ���� �����ϴ� �������.
cbuffer Camera : register(b1)
{
	matrix view;
	matrix projection;
	float3 position;
	float padding;
}

VSOutput main(VSInput input)
{
	VSOutput output;

	// ���� ��ǥ�� ��ȯ.
	output.position = float4(input.position, 1);

	// ���� ��ȯ(���� ��ȯ).
	output.position = mul(output.position, world);
	output.position = mul(output.position, view);
	output.position = mul(output.position, projection);

	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}