struct PSInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// 텍스처.
Texture2D map : register(t0);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// 샘플링 (색상 추출).
	float4 mapColor = map.Sample(mapSampler, input.texCoord);
	//return float4(input.color, 1);
	return mapColor;
}