#pragma once
#include "Behavior.h"
#include "Camera.h"

class Render :public Behavior {
public:
	int mid;
	Vec3 scaling;
	std::shared_ptr<Plane> plane = nullptr;
	std::shared_ptr<Cube> cube = nullptr;
	std::shared_ptr<SphereModel> sphere = nullptr;
	std::shared_ptr<StaticModel> smodel = nullptr;
	std::shared_ptr<AnimatedModel> ani = nullptr;
	std::shared_ptr<AlphaStaticModel> smodelalpha = nullptr;
	std::shared_ptr<AlphaAnimatedModel> anialpha = nullptr;
	std::shared_ptr<AnimationInstance> animatedInstance = nullptr;

public:
	Render(std::string modelname,std::string texturename,int modelID=0,int instanceID=-1,Vec3 s=Vec3(1,1,1)) {
		SetTypeID();
		state = 2;
		mid = modelID;
		auto window = System::window.get();
		auto core = System::core.get();
		auto shaders = System::shaders.get();
		auto psos = System::psos.get();
		auto timer = System::timer.get();
		scaling = s;
		std::string shadername = "s" + std::to_string(id);
		switch (mid)
		{
		case 0:
			if (instanceID>0) {
				for (int i = 0; i < System::smodels.size(); i++) {
					if (instanceID == System::smodels[i]->id) {
						smodel = System::smodels[i];
						break;
					}
				}
			}
			else
			{
				smodel = std::make_shared<StaticModel>();
				smodel->load(core, modelname, shaders, psos, texturename, shadername);
			}	
			break;
		case 1:
			if (instanceID > 0) {
				for (int i = 0; i < System::anis.size(); i++) {
					if (instanceID == System::anis[i]->id) {
						ani = System::anis[i];
						break;
					}
				}
			}
			else
			{
				ani = std::make_shared<AnimatedModel>();
				ani->load(core, modelname, shaders, psos, texturename, shadername);
			}
			animatedInstance = std::make_shared<AnimationInstance>();
			animatedInstance->init(&(ani->animation), 0);
			break;
		case 2:
			if (instanceID > 0) {
				for (int i = 0; i < System::planes.size(); i++) {
					if (instanceID == System::planes[i]->id) {
						plane = System::planes[i];
						break;
					}
				}
			}
			else
			{
				plane = std::make_shared<Plane>();
				plane->init(core, psos, shaders, texturename, shadername);
			}
			break;
		case 3:
			if (instanceID > 0) {
				for (int i = 0; i < System::cubes.size(); i++) {
					if (instanceID == System::cubes[i]->id) {
						cube = System::cubes[i];
						break;
					}
				}
			}
			else
			{
				cube = std::make_shared<Cube>();
				cube->init(core, psos, shaders, texturename, shadername);
			}
			break;
		case 4:
			if (instanceID > 0) {
				for (int i = 0; i < System::spheres.size(); i++) {
					if (instanceID == System::spheres[i]->id) {
						sphere = System::spheres[i];
						break;
					}
				}
			}
			else
			{
				sphere = std::make_shared<SphereModel>();
				sphere->init(core, psos, shaders, texturename, shadername);
			}	
			break;
		case 5:
			if (instanceID > 0) {
				for (int i = 0; i < System::smodelalphas.size(); i++) {
					if (instanceID == System::smodelalphas[i]->id) {
						smodelalpha = System::smodelalphas[i];
						break;
					}
				}
			}
			else
			{
				smodelalpha = std::make_shared<AlphaStaticModel>();
				smodelalpha->load(core, modelname, shaders, psos, texturename, shadername);
			}
			break;
		case 6:
			if (instanceID > 0) {
				for (int i = 0; i < System::anialphas.size(); i++) {
					if (instanceID == System::anialphas[i]->id) {
						anialpha = System::anialphas[i];
						break;
					}
				}
			}
			else
			{
				anialpha = std::make_shared<AlphaAnimatedModel>();
				anialpha->load(core, modelname, shaders, psos, texturename, shadername);
			}		
			animatedInstance = std::make_shared<AnimationInstance>();
			animatedInstance->init(&(anialpha->animation), 0);
			break;
		default:
			break;
		}
	}
	void thirdUpdate() override {
		auto window = System::window.get();
		auto core = System::core.get();
		auto shaders = System::shaders.get();
		auto psos = System::psos.get();
		auto timer = System::timer.get();
		float dt = timer->deltaTime;
		auto obj = GetGameObject();
		//Matrix mvp;
		Matrix m;
		m = (obj->transform.rotation.Inverse()).toMatrix() * Matrix::CreateTranslation(obj->transform.position);
		Matrix vp = System::mainCamera->GetComponent<Camera>()->vp;
		//mvp = m * vp;
		Matrix W;
		W = Matrix::CreateScaling(Vec3(-0.01f, -0.01f, -0.01f)) * Matrix::CreateScaling(scaling) * m;
		switch (mid)
		{
		case 0:
			smodel->updateWorld(shaders, W);
			smodel->draw(core, psos, shaders, vp);
			break;
		case 1:
			animatedInstance->update("run", dt);
			if (animatedInstance->animationFinished() == true)
			{
				animatedInstance->resetAnimationTime();
			}
			ani->draw(core, psos, shaders, animatedInstance.get(), vp, W);
			break;
		case 2:
			W = Matrix::CreateScaling(Vec3(-1.f, -1.f, -1.f)) * Matrix::CreateScaling(scaling) * m;
			plane->draw(core, psos, shaders, vp, W);
			break;
		case 3:
			W = Matrix::CreateScaling(Vec3(-1.f, -1.f, -1.f)) * Matrix::CreateScaling(scaling) * m;
			cube->draw(core, psos, shaders, vp, W);
			break;
		case 4:
			W = Matrix::CreateScaling(Vec3(-1.f, -1.f, -1.f)) * Matrix::CreateScaling(scaling) * m;
			sphere->draw(core, psos, shaders, vp, W);
			break;
		case 5:
			smodelalpha->updateWorld(shaders, W);
			smodelalpha->draw(core, psos, shaders, vp);
			break;
		case 6:
			animatedInstance->update("run", dt);
			if (animatedInstance->animationFinished() == true)
			{
				animatedInstance->resetAnimationTime();
			}
			anialpha->draw(core, psos, shaders, animatedInstance.get(), vp, W);
			break;
		default:
			break;
		}	
	}
};