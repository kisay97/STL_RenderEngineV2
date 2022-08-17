// ���� ���̴� �Է�.
struct VSInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float2 texCoord : TEXCOORD;
    float3 normal : NORMAL;
    float3 binormal : BINORMAL;
    float3 tangent : TANGENT;
};

// ���� ���̴� ��� -> �ȼ� ���̴��� �Է�.
struct VSOutput
{
    float4 position : SV_POSITION;
    float3 texCoord : TEXCOORD;
};

// ��� ����.
cbuffer Transform : register(b0)
{
	// ���
	//float4x4 
    matrix world;
};

// ī�޶��� �����/�������/��ġ ���� �����ϴ� �������.
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