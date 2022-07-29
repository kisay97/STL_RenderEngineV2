struct PSInput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// �ؽ�ó.
Texture2D map : register(t0);
SamplerState mapSampler : register(s0);

float4 main(PSInput input) : SV_TARGET
{
	// ���ø� (���� ����).
	float4 mapColor = map.Sample(mapSampler, input.texCoord);
	//return float4(input.color, 1);
	return mapColor;
}