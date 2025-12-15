#pragma once
#include "Behavior.h"

class Enemy :public Behavior {
public:
	float speed;

	Enemy(float speed_ = 3) { SetTypeID(); speed = speed_; }
	void update() override {
		auto cam = System::mainCamera;
		auto window = System::window;
		auto timer = System::timer;
		float dt = timer->deltaTime;
		auto role = GetGameObject();
		auto player = System::player;

		if (Distance3(role->transform.position, player->transform.position) > 1) {
			role->transform.Translate(Dir3(role->transform.position, player->transform.position)*speed*dt);
			Quaternion q = Quaternion::FromEulerYXZ(0, 180, 0);
			role->transform.rotation = q*player->transform.rotation;
		}
		else
		{
			role->transform.position = Vec3(50, 0, 50);
			System::gameState = 2;
		}
	}
};