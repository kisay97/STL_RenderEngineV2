#pragma once

#include <Core/Core.h>

// 카메라 정보 전달을 위해 인클루드.
#include "Math/Matrix4f.h"
#include "Math/Vector3f.h"

#include "Math/MathHelper.h"

// 상수 버퍼.
#include "Renderer/ConstantBuffer.h"

// 컴포넌트.
#include "Component.h"

namespace STL
{
	// 상수 버퍼에 담을 데이터용 구조체 선언.
	// ex)java,c# -> 구조체: 스택. 클래스: 참조 타입.
	// 16바이트 정렬이 필수.
	struct CameraBufferData
	{
		CameraBufferData()
			: viewMatrix(),
			projectionMatrix(),
			position(), padding(0.0f)
		{
		}

		Matrix4f viewMatrix;			// 뷰 변환 행렬.
		Matrix4f projectionMatrix;		// 투영 변환 행렬.
		Vector3f position;				// 카메라 위치.
		float padding;					// 패딩 값(데이터로는 의미 x, CameraBufferData는 쉐이더로 넘기는 데이터인데 16바이트의 배수로 맞추면 빠르게 동작해서 넣어줌).
										// 변수들 위치의 의미도 있음.
										// 16바이트씩 읽기 때문에 Matrix4f와 Vector3f의 위치가 바뀌면 안됨(Vector3f는 12바이트인데 16바이트씩 읽기 때문에 Matrix4f를 읽을 때 데이터가 짤려서 잘못 읽힌다.)
	};

	class ENGINE_API CameraComponent : public Component
	{
		// RTTI 선언.
		RTTI_DECLARATIONS(CameraComponent, Component)

	public:
		CameraComponent();
		CameraComponent(float width, float height);
		CameraComponent(float fov, float width, float height,
			float zNear, float zFar);
		virtual ~CameraComponent();

		// Inherited via Component
		virtual void Create(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

	protected:

		// 뷰행렬/투영행렬 갱신 메소드.
		virtual void UpdateViewMatrix();
		virtual void UpdateProjectionMatrix();

		// 기본 값.
		static constexpr float DefaultFieldOfView
			= 90.0f * MathHelper::Deg2Rad;
		static constexpr float DefaultWidth = 1280.0f;
		static constexpr float DefaultHeight = 800.0f;
		static constexpr float DefaultNearPlaneDistance = 0.1f; // 기본 근평면(카메라가 잡을 수 있는 가장 가까운 거리) 거리(cm 단위)
		static constexpr float DefaultFarPlaneDistance = 10000.0f; // 기본 원평면(카메라가 잡을 수 있는 가장 먼 거리) 거리(cm 단위)

		// 투영 변환 행렬에 필요한 변수.
		float fieldOfView;			// 시야각(화각).
		float width;				// 화면 가로 크기(1280).
		float height;				// 화면 세로 크기(800).
		float nearPlaneDistance;	// 뷰 프러스텀의 근평면 거리.
		float farPlaneDistance;		// 뷰 프러스텀의 원평면 거리.

		// 카메라 버퍼 관련 변수.
		CameraBufferData bufferData;
		ConstantBuffer cameraBuffer;
	};
}