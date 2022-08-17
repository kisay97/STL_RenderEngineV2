// 램버트 쉐이더 - 디퓨즈.
float ComputeLambert(float3 worldNormal, float3 lightDirection)
{
	return saturate(dot(worldNormal, -lightDirection));
}

// 하프 램버트 쉐이더 - 디퓨즈(난반사).
float ComputeHalfLambert(float3 worldNormal, float3 lightDirection)
{
	float NdotL = dot(worldNormal, -lightDirection);
	NdotL = pow(NdotL * 0.5f + 0.5f, 2);

	return NdotL;
}

// 퐁 쉐이더 - 스페큘러(정반사).
float ComputePhong(float NdotL, float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shiness)
{
	// 반사 벡터 구하기.
    float3 reflection = reflect(-lightDirection, worldNormal); // 언급: 반사벡터 R은 입사벡터 + 2노멀벡터(-입사벡터*노멀벡터). 코드는 reflect 함수를 썼지만 직접 구해도 됨.

	// 스페큘러 구하기.
	float specularPower = 0.0f;

	// 빛의 강도가 있는 경우에만 정반사 계산.
	if (NdotL > 0.0f)
	{
		float RdotV = dot(reflection, cameraDirection); // 반사벡터 (내적) 카메라벡터.
        specularPower = pow(saturate(RdotV), shiness); // 위에 계산을 하면 넓은 영역이 구해짐. 따라서 특정 부분이 반짝일 수 있게 제곱을 해서 영역을 좁힘
    }

	return specularPower;
}

// 블린-퐁 쉐이더 - 스페큘러(정반사). 언급: 반사벡터가 구하기가 어려워서 나온 공식. 품질을 좋게 하는게 아니라 성능을 고려해서 나온거임.
float ComputeBlinnPhong(float NdotL, float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shiness)
{
	// 하프 벡터 구하기. 언급: 카메라벡터와 입사벡터를 더하면 반사벡터와 비슷해진다.
	float3 halfVector = normalize((-lightDirection) + (-cameraDirection));

	float specularPower = 0.0f;
	if (NdotL > 0.0f)
	{
		float HdotN = dot(halfVector, worldNormal);
        specularPower = pow(saturate(HdotN), shiness);
    }

	return specularPower;
}

// 림 라이트.
float4 ComputeRimPower(float3 rimColor, float3 worldNormal, float3 cameraDirection, float rimConstant)
{
    float3 rim = saturate(dot(-cameraDirection, worldNormal));
    rim = pow(1 - rim, (rimConstant*0.5f)) * rimColor;
	
    return float4(rim, 1);
}