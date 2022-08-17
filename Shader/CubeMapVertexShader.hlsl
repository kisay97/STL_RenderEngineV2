// 정점 쉐이더 입력.
struct VSInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 binormal : BINORMAL;
    float3 tangent : TANGENT;
};

// 정점 쉐이더 출력 -> 픽셀 쉐이더의 입력.
struct VSOutput
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

// 상수 버퍼.
cbuffer Transform : register(b0)
{
	// 행렬
	//float4x4 
    matrix world;
};

// 카메라의 뷰행렬/투영행렬/위치 값을 전달하는 상수버퍼.
cbuffer Camera : register(b1)
{
    matrix view;
    matrix projection;
    float3 position;
    float padding;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    output.position = mul(float4(input.position, 1), world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    output.texCoord = input.position.xyz;
	return output;
}