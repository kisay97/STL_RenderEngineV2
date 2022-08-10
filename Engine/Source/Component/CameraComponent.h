#pragma once

#include <Core/Core.h>

// ī�޶� ���� ������ ���� ��Ŭ���.
#include "Math/Matrix4f.h"
#include "Math/Vector3f.h"

#include "Math/MathHelper.h"

// ��� ����.
#include "Renderer/ConstantBuffer.h"

// ������Ʈ.
#include "Component.h"

namespace STL
{
	// ��� ���ۿ� ���� �����Ϳ� ����ü ����.
	// ex)java,c# -> ����ü: ����. Ŭ����: ���� Ÿ��.
	// 16����Ʈ ������ �ʼ�.
	struct CameraBufferData
	{
		CameraBufferData()
			: viewMatrix(),
			projectionMatrix(),
			position(), padding(0.0f)
		{
		}

		Matrix4f viewMatrix;			// �� ��ȯ ���.
		Matrix4f projectionMatrix;		// ���� ��ȯ ���.
		Vector3f position;				// ī�޶� ��ġ.
		float padding;					// �е� ��(�����ͷδ� �ǹ� x, CameraBufferData�� ���̴��� �ѱ�� �������ε� 16����Ʈ�� ����� ���߸� ������ �����ؼ� �־���).
										// ������ ��ġ�� �ǹ̵� ����.
										// 16����Ʈ�� �б� ������ Matrix4f�� Vector3f�� ��ġ�� �ٲ�� �ȵ�(Vector3f�� 12����Ʈ�ε� 16����Ʈ�� �б� ������ Matrix4f�� ���� �� �����Ͱ� ©���� �߸� ������.)
	};

	class ENGINE_API CameraComponent : public Component
	{
		// RTTI ����.
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

		// �����/������� ���� �޼ҵ�.
		virtual void UpdateViewMatrix();
		virtual void UpdateProjectionMatrix();

		// �⺻ ��.
		static constexpr float DefaultFieldOfView
			= 90.0f * MathHelper::Deg2Rad;
		static constexpr float DefaultWidth = 1280.0f;
		static constexpr float DefaultHeight = 800.0f;
		static constexpr float DefaultNearPlaneDistance = 0.1f; // �⺻ �����(ī�޶� ���� �� �ִ� ���� ����� �Ÿ�) �Ÿ�(cm ����)
		static constexpr float DefaultFarPlaneDistance = 10000.0f; // �⺻ �����(ī�޶� ���� �� �ִ� ���� �� �Ÿ�) �Ÿ�(cm ����)

		// ���� ��ȯ ��Ŀ� �ʿ��� ����.
		float fieldOfView;			// �þ߰�(ȭ��).
		float width;				// ȭ�� ���� ũ��(1280).
		float height;				// ȭ�� ���� ũ��(800).
		float nearPlaneDistance;	// �� ���������� ����� �Ÿ�.
		float farPlaneDistance;		// �� ���������� ����� �Ÿ�.

		// ī�޶� ���� ���� ����.
		CameraBufferData bufferData;
		ConstantBuffer cameraBuffer;
	};
}