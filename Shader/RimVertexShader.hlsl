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
    float3 color : COLOR;
    float2 texCoord : TEXCOORD0;
    float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;
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
    float3 cameraPosition;
    float padding;
};

VSOutput main(VSInput input)
{
    VSOutput output;
    
    // ���� ���� ��ȯ - ���� -> ���� ����.
    output.position = mul(float4(input.position, 1), world);
    
    // ī�޶� ���� ���ϱ�.
    output.cameraDirection = normalize(output.position.xyz - cameraPosition);
    
    // ���� ���� ��ȯ - ���� -> �� -> ���� ����.
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    // ��� ���� ��ȯ - ���� -> ���� ����.
    output.normal = normalize(mul(input.normal, (float3x3) world));
    
    output.texCoord = input.texCoord;
    output.color = input.color;

    return output;
}