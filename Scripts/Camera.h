#pragma once
#include "Behavior.h"

class Camera :public Behavior {
public:
	Matrix vp;
	Vec3 magnification=Vec3(1,1,1);
	Camera() { SetTypeID(); state = 2; }
	void Start() override {
		auto cam = GetGameObject();
		auto player = System::player;
		cam->transform.position = player->transform.position - player->transform.front()*6+ player->transform.up() * 5;
		cam->transform.rotation = player->transform.rotation;

		Matrix p = Matrix::perspective(0.01f, 10000.0f, WIDTH / HEIGHT, 60.0f);
		Matrix v = Matrix::lookAt(cam->transform.position, cam->transform.position + cam->transform.front(), Vec3(0, 1, 0));
		vp = v * Matrix::CreateScaling(magnification) *p;
	}

	void thirdUpdate() override {
		auto cam = GetGameObject();
		auto player = System::player;
		cam->transform.position = player->transform.position - player->transform.front() * 6 + player->transform.up() * 5;
		Matrix p = Matrix::perspective(0.01f, 10000.0f, WIDTH / HEIGHT, 60.0f);
		Matrix v = Matrix::lookAt(cam->transform.position, cam->transform.position + cam->transform.front(), Vec3(0, 1, 0));		
		vp = v * Matrix::CreateScaling(magnification) * p;
		System::vp = Matrix::lookAt(Vec3(0,0,0), cam->transform.front(), Vec3(0, 1, 0)) * p;
	}
};