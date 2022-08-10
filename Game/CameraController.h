#pragma once

#include <Core/Core.h>
#include "Component/Component.h"

namespace STL
{
	class KeyboardInput;
	class MouseInput;
	class CameraController : public Component
	{
		RTTI_DECLARATIONS(CameraController, Component)
	public:
		CameraController();
		~CameraController();

		// Component을(를) 통해 상속됨
		virtual void Create(ID3D11Device* device) override;
		virtual void Update(ID3D11DeviceContext* context, float deltaTime) override;
		virtual void Bind(ID3D11DeviceContext* context) override;

		void SetKeyboard(KeyboardInput* keyboard);
		void SetMouse(MouseInput* mouse);

		void SetMoveSpeed(float moveSpeed);
		void SetRotateSpeed(float rotateSpeed);

	private:

		void MoveCamera(float deltaTime);
		void RotateCamera(float deltaTime);

		KeyboardInput* keyboard;
		MouseInput* mouse;
		float moveSpeed;
		float rotateSpeed;
	};
}