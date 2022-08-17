struct PSInput
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

// 텍스처 / 샘플러 스테이트.
TextureCube cubemapTexture;
SamplerState cubemapSampler;

float4 main(PSInput input) : SV_TARGET
{
    float3 environment = cubemapTexture.Sample(cubemapSampler, input.texCoord).rgb;
    return float4(environment, 1.0f);
}