#include "Camera.h"
#include "../ImGui/imgui.h"

namespace {
	static float distance = 500.0f; // ƒLƒƒƒ‰‚©‚ç‚Ì‹——£
	static float lookHeight = 200.0f; // ’Ž‹“_‚Ì‚‚³
};

Camera::Camera()
{
	GetMousePoint(&prevX, &prevY);
	transform.rotation.y = 20.0f * DegToRad;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	int moveX = mouseX - prevX;
	int moveY = mouseY - prevY;
	prevX = mouseX;
	prevY = mouseY;

	VECTOR3& rot = transform.rotation;
	rot.y += 0.5f * DegToRad * moveX;
	rot.x -= 0.4f * DegToRad * moveY;
	if (rot.x >= 85.0f * DegToRad) {
		rot.x = 85.0f * DegToRad;
	}
	if (rot.x < -60.0f * DegToRad) {
		rot.x = -60.0f * DegToRad;
	}

	ImGui::Begin("Camera");
	ImGui::InputFloat("RotX", &rot.x);
	ImGui::InputFloat("RotY", &rot.y);
	ImGui::InputFloat("RotZ", &rot.z);
	ImGui::End();

	VECTOR3 camPos = VECTOR3(0, 0, -500.0f)
							* MGetRotX(rot.x)
							* MGetRotY(rot.y);
	SetCameraPositionAndTarget_UpVecY(
			lookPosition + VECTOR3(0, 150, 0)+camPos,
			lookPosition + VECTOR3(0, 200.0f, 0));
}

void Camera::Draw()
{
}

void Camera::SetPlayerPosition(const VECTOR& pos)
{
	lookPosition = pos;
}
