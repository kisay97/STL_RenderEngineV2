#include "Core.h"
#include "TransformComponent.h"

namespace STL
{
	TransformComponent::TransformComponent()
		: position(), rotation(), scale(Vector3f::One),
		isDirty(false), transformMatrix()
	{
		transformMatrix = Matrix4f::Identity();
	}

	TransformComponent::~TransformComponent()
	{
	}
	
	void TransformComponent::Create(ID3D11Device* device)
	{
		// ��� ����.
		transformMatrix = 
			Matrix4f::Scale(scale)
			* Matrix4f::Rotation(rotation)
			* Matrix4f::Translation(position);

		// Ʈ������ ���� ����.
		transformBuffer = ConstantBuffer(&transformMatrix, 1, sizeof(Matrix4f));
		transformBuffer.Create(device);
	}
	
	void TransformComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// ����� ���� ������ ó�� ����.
		if (isDirty == false)
		{
			return;
		}

		// ��� ����.
		transformMatrix =
			Matrix4f::Scale(scale)
			* Matrix4f::Rotation(rotation)
			* Matrix4f::Translation(position);

		// Ʈ������ ���� ������Ʈ(����)
		transformBuffer.Update(context, &transformMatrix);

		// dirty bit �ʱ�ȭ.
		isDirty = false;
	}
	
	void TransformComponent::Bind(ID3D11DeviceContext* context)
	{
		// �׷��� ī�忡 ����(����).
		transformBuffer.Bind(context, 0);
	}
	
	// Ʈ�������� ȸ�� ���� �������� �� ���� ���ϱ�
	Vector3f TransformComponent::Forword() const
	{
		Vector3f rot = rotation;
		Matrix4f orientation = Matrix4f::Rotation(rot); // ȸ�� ��� �����
		return orientation * Vector3f::Forward; //���� �չ��⿡�� ���Ѵ�. (���� ������ �չ����� �� ȸ������ŭ ȸ����Ŵ)
	}
	
	Vector3f TransformComponent::Right() const
	{
		Vector3f rot = rotation;
		Matrix4f orientation = Matrix4f::Rotation(rot);
		return orientation * Vector3f::Right;
	}
	
	Vector3f TransformComponent::Up() const
	{
		Vector3f rot = rotation;
		Matrix4f orientation = Matrix4f::Rotation(rot);
		return orientation * Vector3f::Up;
	}
	
	void TransformComponent::SetPosition(float x, float y, float z)
	{
		position = Vector3f(x, y, z);
		SetDirty(); //TRS�� �ٲ������ SetDirty()�� ���ش�.
	}
	
	void TransformComponent::SetPosition(const Vector3f& position)
	{
		this->position = position;
		SetDirty();
	}
	
	Vector3f TransformComponent::Position() const
	{
		return position;
	}
	
	void TransformComponent::SetRotation(float x, float y, float z)
	{
		rotation = Vector3f(x, y, z);
		SetDirty();
	}
	
	void TransformComponent::SetRotation(const Vector3f& rotation)
	{
		this->rotation = rotation;
		SetDirty();
	}
	
	Vector3f TransformComponent::Rotation() const
	{
		return rotation;
	}
	
	void TransformComponent::SetScale(float x, float y, float z)
	{
		scale = Vector3f(x, y, z);
		SetDirty();
	}
	
	void TransformComponent::SetScale(const Vector3f& scale)
	{
		this->scale = scale;
		SetDirty();
	}
	
	Vector3f TransformComponent::Scale() const
	{
		return scale;
	}
	
	void TransformComponent::SetDirty()
	{
		isDirty = true;
	}
}