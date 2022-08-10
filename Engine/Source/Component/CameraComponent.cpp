#include "Core.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "TransformComponent.h"
#include "Math/Quaternionf.h"

namespace STL
{	
	CameraComponent::CameraComponent()
		: CameraComponent(
			DefaultFieldOfView,
			DefaultWidth,
			DefaultHeight,
			DefaultNearPlaneDistance,
			DefaultFarPlaneDistance)
	{
	}

	CameraComponent::CameraComponent(float width, float height)
		: CameraComponent(
			DefaultFieldOfView,
			width,
			height,
			DefaultNearPlaneDistance,
			DefaultFarPlaneDistance)
	{
	}

	CameraComponent::CameraComponent(
		float fov, float width, float height,
		float zNear, float zFar)
		: fieldOfView(fov), width(width), height(height),
		nearPlaneDistance(zNear), farPlaneDistance(zFar)
	{
	}

	CameraComponent::~CameraComponent()
	{
	}

	void CameraComponent::Create(ID3D11Device* device)
	{
		UpdateViewMatrix();
		UpdateProjectionMatrix();

		bufferData.position = transform->Position();
		cameraBuffer = ConstantBuffer(&bufferData, 1, sizeof(bufferData));
		cameraBuffer.Create(device);
	}

	void CameraComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		UpdateViewMatrix();

		cameraBuffer.Update(context, &bufferData);
	}

	void CameraComponent::Bind(ID3D11DeviceContext* context)
	{
		cameraBuffer.Bind(context, 1);
	}

	// 뷰 행렬 갱신 함수.
	void CameraComponent::UpdateViewMatrix()
	{
		if (transform == nullptr)
		{
			transform = ownerActor->transform.get();
		}

		// #1.
		// 역행렬 구하는 방식 - 엔진에서 주로 사용하는 방식.
		// 위치 변환 행렬의 역행렬 = (-x, -y, -z)의 행렬.
		// 회전 변환 행렬의 역행렬 = Rx의 전치 * Ry의 전치 * Rz의 전치행렬.
		bufferData.viewMatrix =
			Matrix4f::Translation(transform->Position() * -1.0f)
			//* Matrix4f::InverseRotationMatrix(transform->Rotation());
			* transform->Rotation().ToQuaternion().Inverse().ToMatrix4f();
		bufferData.position = transform->Position();

		// #2.
		// DX(DirectXMath/XNAMath) / OpenGL(glm) 수학 라이브러리 기본 방식.
		//Vector3f position = transform->Position();
		//Vector3f forward = Vector3f::Forward;
		//forward *= 10.0f;
		//Vector3f up = Vector3f::Up;
		//bufferData.viewMatrix = Matrix4f::LookAt(position, forward, up);
	}

	void CameraComponent::UpdateProjectionMatrix()
	{
		//bufferData.projectionMatrix = Matrix4f::Identity();
		bufferData.projectionMatrix = Matrix4f::Perspective(
			fieldOfView, width, height, nearPlaneDistance, farPlaneDistance
		);
	}
}