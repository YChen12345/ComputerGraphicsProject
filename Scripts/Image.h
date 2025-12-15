#pragma once
#include "Behavior.h"
#include "Camera.h"

class Image :public Behavior {
public:
	std::string iname;
	Vec3 scale;
	UI ui;

public:
	Image(std::string texturename,Vec3 s=Vec3(1,1,1)) {
		SetTypeID();
		iname = texturename;
		state = 2;
		scale = s;
		auto window = System::window.get();
		auto core = System::core.get();
		auto shaders = System::shaders.get();
		auto psos = System::psos.get();
		auto timer = System::timer.get();
		std::string shadername = "s" + std::to_string(id);
		ui.init(core, psos, shaders, iname, shadername);
	}
	void uiRender() override {
		auto window = System::window.get();
		auto core = System::core.get();
		auto shaders = System::shaders.get();
		auto psos = System::psos.get();
		auto timer = System::timer.get();
		float dt = timer->deltaTime;
		auto obj = GetGameObject();
		auto cam = System::mainCamera;
		Matrix vp;
		Matrix p = Matrix::perspective(0.01f, 10000.0f, 1920.0f / 1080.0f, 60.0f);
		Matrix v = Matrix::lookAt(Vec3(0,0,-1), Vec3(0, 0, 0), Vec3(0, 1, 0));
		vp = v * p;
		Matrix W = Matrix::CreateScaling(Vec3(1,-1,-1))*Matrix::CreateScaling(scale);
		ui.draw(core, psos, shaders, vp, W);
	}
};