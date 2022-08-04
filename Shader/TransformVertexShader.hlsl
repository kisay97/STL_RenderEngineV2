// 정점 쉐이더 입력.
struct VSInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// 정점 쉐이더 출력 -> 픽셀 쉐이더의 입력.
struct VSOutput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// 상수 버퍼.
cbuffer Transform : register(b0)
{
	// 행렬
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