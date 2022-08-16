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
    float3 color : COLOR;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
    float3 binormal : TEXCOORD2;
    float3 tangent : TEXCOORD3;
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
    float3 cameraPosition;
    float padding;
};

VSOutput main(VSInput input)
{
    VSOutput output;
	
	// 동차좌표로 변환.
    output.position = float4(input.position, 1);
	
	// 정점 변환(공간 변환).
    output.position = mul(output.position, world);
	
	// 카메라 방향.
    output.cameraDirection = normalize((float3) output.position - cameraPosition);
	
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
	
    output.color = input.color;
    output.texCoord = input.texCoord;
	
	// 노멀도 로컬 -> 월드 공간으로 변환.
    output.normal = mul(input.normal, (float3x3)world);
    
    // 바이노멀/탄젠트 로컬 -> 월드 공간으로 변환.
    output.binormal = mul(input.binormal, (float3x3)world);
    output.tangent = mul(input.tangent, (float3x3)world);

    return output;
}