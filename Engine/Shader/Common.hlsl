float ComputeLambert(float3 worldNormal, float3 lightDirection)
{
	return saturate(dot(worldNormal, -lightDirection));
}

float ComputeHalfLambert(float3 worldNormal, float3 lightDirection)
{
	float NdotL = dot(worldNormal, -lightDirection);
	NdotL = pow(NdotL * 0.5f + 0.5f, 2);

	return NdotL;
}

float ComputePhong(float NdotL, float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shiness)
{
    float3 reflection = reflect(-lightDirection, worldNormal);

	float specularPower = 0.0f;
	if (NdotL > 0.0f)
	{
		float RdotV = dot(reflection, cameraDirection);
        specularPower = pow(saturate(RdotV), shiness);
    }

	return specularPower;
}

float ComputeBlinnPhong(float NdotL, float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shiness)
{
	float3 halfVector = normalize((-lightDirection) + (-cameraDirection));

	float specularPower = 0.0f;
	if (NdotL > 0.0f)
	{
		float HdotN = dot(halfVector, worldNormal);
        specularPower = pow(saturate(HdotN), shiness);
    }

	return specularPower;
}