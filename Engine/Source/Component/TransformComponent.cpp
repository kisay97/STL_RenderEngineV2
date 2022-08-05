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
		// 행렬 설정.
		transformMatrix = 
			Matrix4f::Scale(scale)
			* Matrix4f::Rotation(rotation)
			* Matrix4f::Translation(position);

		// 트랜스폼 버퍼 생성.
		transformBuffer = ConstantBuffer(&transformMatrix, 1, sizeof(Matrix4f));
		transformBuffer.Create(device);
	}
	
	void TransformComponent::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		// 변경된 값이 없으면 처리 안함.
		if (isDirty == false)
		{
			return;
		}

		// 행렬 설정.
		transformMatrix =
			Matrix4f::Scale(scale)
			* Matrix4f::Rotation(rotation)
			* Matrix4f::Translation(position);

		// 트랜스폼 버퍼 업데이트(갱신)
		transformBuffer.Update(context, &transformMatrix);

		// dirty bit 초기화.
		isDirty = false;
	}
	
	void TransformComponent::Bind(ID3D11DeviceContext* context)
	{
		// 그래픽 카드에 전달(연결).
		transformBuffer.Bind(context, 0);
	}
	
	// 트랜스폼의 회전 값을 기준으로 앞 방향 구하기
	Vector3f TransformComponent::Forword() const
	{
		Vector3f rot = rotation;
		Matrix4f orientation = Matrix4f::Rotation(rot); // 회전 행렬 만들고
		return orientation * Vector3f::Forward; //원래 앞방향에다 곱한다. (월드 방향의 앞방향을 내 회전값만큼 회전시킴)
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
		SetDirty(); //TRS가 바뀌었으니 SetDirty()를 해준다.
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