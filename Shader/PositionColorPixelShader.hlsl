struct PSInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
};

float nrand(float2 uv)
{
	return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

float4 main(PSInput input) : SV_TARGET
{
	return float4(
		float3(
			nrand(float2(input.color.x, input.color.y)),
			nrand(float2(input.color.y, input.color.z)),
			nrand(float2(input.color.z, input.color.x))
		),
		1
	);
}