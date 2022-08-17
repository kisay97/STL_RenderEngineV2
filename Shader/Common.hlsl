// ����Ʈ ���̴� - ��ǻ��.
float ComputeLambert(float3 worldNormal, float3 lightDirection)
{
	return saturate(dot(worldNormal, -lightDirection));
}

// ���� ����Ʈ ���̴� - ��ǻ��(���ݻ�).
float ComputeHalfLambert(float3 worldNormal, float3 lightDirection)
{
	float NdotL = dot(worldNormal, -lightDirection);
	NdotL = pow(NdotL * 0.5f + 0.5f, 2);

	return NdotL;
}

// �� ���̴� - ����ŧ��(���ݻ�).
float ComputePhong(float NdotL, float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shiness)
{
	// �ݻ� ���� ���ϱ�.
    float3 reflection = reflect(-lightDirection, worldNormal); // ���: �ݻ纤�� R�� �Ի纤�� + 2��ֺ���(-�Ի纤��*��ֺ���). �ڵ�� reflect �Լ��� ������ ���� ���ص� ��.

	// ����ŧ�� ���ϱ�.
	float specularPower = 0.0f;

	// ���� ������ �ִ� ��쿡�� ���ݻ� ���.
	if (NdotL > 0.0f)
	{
		float RdotV = dot(reflection, cameraDirection); // �ݻ纤�� (����) ī�޶���.
        specularPower = pow(saturate(RdotV), shiness); // ���� ����� �ϸ� ���� ������ ������. ���� Ư�� �κ��� ��¦�� �� �ְ� ������ �ؼ� ������ ����
    }

	return specularPower;
}

// ��-�� ���̴� - ����ŧ��(���ݻ�). ���: �ݻ纤�Ͱ� ���ϱⰡ ������� ���� ����. ǰ���� ���� �ϴ°� �ƴ϶� ������ ����ؼ� ���°���.
float ComputeBlinnPhong(float NdotL, float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shiness)
{
	// ���� ���� ���ϱ�. ���: ī�޶��Ϳ� �Ի纤�͸� ���ϸ� �ݻ纤�Ϳ� ���������.
	float3 halfVector = normalize((-lightDirection) + (-cameraDirection));

	float specularPower = 0.0f;
	if (NdotL > 0.0f)
	{
		float HdotN = dot(halfVector, worldNormal);
        specularPower = pow(saturate(HdotN), shiness);
    }

	return specularPower;
}

// �� ����Ʈ.
float4 ComputeRimPower(float3 rimColor, float3 worldNormal, float3 cameraDirection, float rimConstant)
{
    float3 rim = saturate(dot(-cameraDirection, worldNormal));
    rim = pow(1 - rim, (rimConstant*0.5f)) * rimColor;
	
    return float4(rim, 1);
}