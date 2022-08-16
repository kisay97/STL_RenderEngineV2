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
    float3 binormal : TEXCOORD2;
    float3 tangent : TEXCOORD3;
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
	
	// ������ǥ�� ��ȯ.
    output.position = float4(input.position, 1);
	
	// ���� ��ȯ(���� ��ȯ).
    output.position = mul(output.position, world);
	
	// ī�޶� ����.
    output.cameraDirection = normalize((float3) output.position - cameraPosition);
	
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
	
    output.color = input.color;
    output.texCoord = input.texCoord;
	
	// ��ֵ� ���� -> ���� �������� ��ȯ.
    output.normal = mul(input.normal, (float3x3)world);
    
    // ���̳��/ź��Ʈ ���� -> ���� �������� ��ȯ.
    output.binormal = mul(input.binormal, (float3x3)world);
    output.tangent = mul(input.tangent, (float3x3)world);

    return output;
}