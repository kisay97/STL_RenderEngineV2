#include "CameraController.h"
#include "Device/KeyboardInput.h"
#include "Device/MouseInput.h"
#include "Component/TransformComponent.h"

namespace STL
{
	CameraController::CameraController()
		: keyboard(nullptr), mouse(nullptr),
		moveSpeed(30.0f), rotateSpeed(20.0f)
	{
	}

	CameraController::~CameraController()
	{
	}

	void CameraController::Create(ID3D11Device* device)
	{
	}

	void CameraController::MoveCamera(float deltaTime)
	{
		float moveAmount = moveSpeed * deltaTime;
		if (keyboard->IsKeyDown(Keys::A))
		{
			Vector3f position = transform->Position();
			position += transform->Right() * -moveAmount;
			transform->SetPosition(position);
		}

		if (keyboard->IsKeyDown(Keys::D))
		{
			Vector3f position = transform->Position();
			position += transform->Right() * moveAmount;
			transform->SetPosition(position);
		}

		if (keyboard->IsKeyDown(Keys::S))
		{
			Vector3f position = transform->Position();
			position += transform->Forward() * -moveAmount;
			transform->SetPosition(position);
		}

		if (keyboard->IsKeyDown(Keys::W))
		{
			Vector3f position = transform->Position();
			position += transform->Forward() * moveAmount;
			transform->SetPosition(position);
		}

		if (keyboard->IsKeyDown(Keys::E))
		{
			Vector3f position = transform->Position();
			position += transform->Up() * moveAmount;
			transform->SetPosition(position);
		}

		if (keyboard->IsKeyDown(Keys::Q))
		{
			Vector3f position = transform->Position();
			position += transform->Up() * -moveAmount;
			transform->SetPosition(position);
		}
	}

	void CameraController::RotateCamera(float deltaTime)
	{
		if (mouse->IsButtonHeldDown(MouseButtons::Left))
		{
			//float rotateAmount = rotateSpeed * deltaTime * 0.1f;
			float rotateAmount = rotateSpeed * deltaTime;
			static float threshold = 1.0f;

			//const auto& state = mouse->CurrentState();
			auto rotation = transform->Rotation();

			rotation.x -= rotateAmount * mouse->DeltaY();
			if (rotation.x >= 360.0f || rotation.x <= -360.0f)
			{
				rotation.x = 0.0f;
			}

			rotation.y -= rotateAmount * mouse->DeltaX();
			if (rotation.y >= 360.0f || rotation.y <= -360.0f)
			{
				rotation.y = 0.0f;
			}
			transform->SetRotation(rotation);
		}
	}

	void CameraController::Update(ID3D11DeviceContext* context, float deltaTime)
	{
		if (keyboard == nullptr || mouse == nullptr)
		{
			return;
		}

		MoveCamera(deltaTime);
		RotateCamera(deltaTime);
	}

	void CameraController::Bind(ID3D11DeviceContext* context)
	{

	}

	void CameraController::SetKeyboard(KeyboardInput* keyboard)
	{
		this->keyboard = keyboard;
	}

	void CameraController::SetMouse(MouseInput* mouse)
	{
		this->mouse = mouse;
	}

	void CameraController::SetMoveSpeed(float moveSpeed)
	{
		this->moveSpeed = moveSpeed;
	}

	void CameraController::SetRotateSpeed(float rotateSpeed)
	{
		this->rotateSpeed = rotateSpeed;
	}
}