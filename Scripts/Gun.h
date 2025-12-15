#pragma once
#include "Behavior.h"
#include "Image.h"
#include "Camera.h"
class Gun :public Behavior {
public:

	Gun() { SetTypeID();}
	void Start() override {
		auto role = GetGameObject();
		Quaternion q = Quaternion::FromEulerYXZ(0, -90, 0);
		role->transform.position = System::player->transform.position;
		role->transform.rotation = q * System::player->transform.rotation;
		role->GetComponent<Image>()->isActive = false;
	}
	void lateUpdate() override {
		auto window = System::window;
		auto cam = System::mainCamera;
		auto role = GetGameObject();
		Quaternion q = Quaternion::FromEulerYXZ(0, -90, 0);
		role->transform.position = System::player->transform.position;
		role->transform.rotation=q* System::player->transform.rotation;

		if (window->GetMouseButtonDown(2)) {
			if (role->GetComponent<Image>()->isActive) {
				role->GetComponent<Image>()->isActive = false;
				cam->GetComponent<Image>()->isActive = true;
				cam->GetComponent<Camera>()->magnification = Vec3(1, 1, 1);
			}
			else
			{
				role->GetComponent<Image>()->isActive = true;
				cam->GetComponent<Image>()->isActive = false;
				cam->GetComponent<Camera>()->magnification = Vec3(2, 2, 1);
			}
		}
	}
};