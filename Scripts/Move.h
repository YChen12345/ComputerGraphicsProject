#pragma once
#include "Behavior.h"

class Move :public Behavior {
public:
	float speed;
	float jump;
	float angleH;
	float angleV;
	int jumpState;
	float jumpHigh;
	float ground;
	float jumptimer;
	float jumpstartheight;

	Move(float speed_ = 6) {
		SetTypeID(); speed = speed_; jump = 18; angleH = 0; angleV = 0; jumpState = 0; ground = 1; jumpHigh = 3; jumptimer = 0; jumpstartheight= 0;
	}
	void Start() override {
		auto role = GetGameObject();
		role->transform.position = Vec3(0, ground, -10);
		role->transform.scaling = Vec3(0.2f, 0.2f, 0.2f);
	}
	void update() override {
		auto cam = System::mainCamera;
		auto window = System::window;
		auto timer = System::timer;
		float dt = timer->deltaTime;
		auto role = GetGameObject();
		if (abs(window->MouseMove().magnitude()) > 1) {
			angleH += (5 * window->MouseMove().x * dt);
			angleV += (5 * window->MouseMove().y * dt);
			angleV = MMax(-30.0f, MMin(angleV, 30.0f));
			Quaternion q = Quaternion::FromEulerYXZ(0, angleH, 0);
			role->transform.rotation = q;
			q = q.FromAxisAngle(q.right(), angleV)*q;
			cam->transform.rotation = q;		
		}
		if (window->GetKey('W'))
		{
			role->transform.Translate
			(Vec3(role->transform.front().x, 0, role->transform.front().z).Normalize() * speed * dt);
		}
		if (window->GetKey('S'))
		{
			role->transform.Translate
			(Vec3(role->transform.front().x, 0, role->transform.front().z).Normalize() * -speed * dt);
		}
		if (window->GetKey('A'))
		{
			role->transform.Translate
			(Vec3(role->transform.right().x, 0, role->transform.right().z).Normalize() * -speed * dt);
		}
		if (window->GetKey('D'))
		{
			role->transform.Translate
			(Vec3(role->transform.right().x, 0, role->transform.right().z).Normalize() * speed * dt);
		}
		if (window->GetKeyDown(VK_SPACE))
		{
			if (jumpState == 0) {
				jumpState = 1;
				jumpstartheight = role->transform.position.y;
			}
		}
		if (jumpState == 1) {
			role->transform.Translate(role->transform.up() * jump * dt);
			
		}
		if (role->transform.position.y > jumpstartheight+jumpHigh) {
			jumpState = 2;
		}
		if (jumpState != 1) {
			role->transform.Translate(role->transform.up() * -jump/2 * dt);
			jumptimer += dt;
		}
		if (jumptimer > 1) {
			jumptimer = 0;
			jumpState = 0;
		}
		if(role->transform.position.y < ground)
		{
			jumpState = 0;
			role->transform.position = Vec3(role->transform.position.x, ground, role->transform.position.z);
		}
		//if (window->GetKey(VK_CONTROL))
		//{
		//	System::mainCamera->transform.Translate(Vec3(0, 1, 0) * -10 * dt);
		//}
	}
};