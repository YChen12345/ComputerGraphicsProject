#pragma once
#include "List.h"
#include "Mathf.h"
#include "Shaders.h"
#include "Mesh.h"
#include "PSO.h"
#include "GEMLoader.h"
#include "Animation.h"
#include "Window.h"
#include "Timer.h"
#include "Model.h"

#define WIDTH 1024
#define HEIGHT 768
class GameObject;

class System {

public:
	inline static int gameState = -1;
	static List<std::shared_ptr<GameObject>> gameobjects;
	inline static std::shared_ptr<GameObject> mainCamera = nullptr;
	inline static std::shared_ptr<GameObject> player = nullptr;
	inline static std::shared_ptr<Window> window = nullptr;
	inline static std::shared_ptr<Core> core = nullptr;
	inline static std::shared_ptr<Shaders> shaders = nullptr;
	inline static std::shared_ptr<PSOManager> psos = nullptr;
	inline static std::shared_ptr<Timer> timer = nullptr;
	inline static std::shared_ptr<SkyBox> skybox = nullptr;

	static std::vector<std::shared_ptr<Plane>> planes;
	static std::vector<std::shared_ptr<Cube>> cubes;
	static std::vector<std::shared_ptr<SphereModel>> spheres;
	static std::vector<std::shared_ptr<StaticModel>> smodels;
	static std::vector<std::shared_ptr<AnimatedModel>> anis;
	static std::vector<std::shared_ptr<AlphaStaticModel>> smodelalphas;
	static std::vector<std::shared_ptr<AlphaAnimatedModel>> anialphas;
	static std::vector<std::shared_ptr<AnimationInstance>> animatedInstances;
	static Matrix vp;

public:
	static void NewGameObject(std::shared_ptr<GameObject> g) {
		gameobjects.Add(g);
	}
	static void LoadModel(std::string modelname, std::string texturename, int modelID,int id) {
		std::string shadername;
		switch (modelID)
		{
		case 0:
		{
			shadername = "shader0" + std::to_string(System::smodels.size());
			auto smodel = std::make_shared<StaticModel>();
			smodel->load(core.get(), modelname, shaders.get(), psos.get(), texturename, shadername);
			smodel->id = id;
			smodels.push_back(smodel);
		}	
		break;
		case 1:
		{
			shadername = "shader1" + std::to_string(System::anis.size());
			auto ani = std::make_shared<AnimatedModel>();
			ani->load(core.get(), modelname, shaders.get(), psos.get(), texturename, shadername);
			ani->id = id;
			anis.push_back(ani);
		}
		break;
		case 2:
		{
			shadername = "shader2" + std::to_string(System::planes.size());
			auto plane = std::make_shared<Plane>();
			plane->init(core.get(), psos.get(), shaders.get(), texturename, shadername);
			plane->id = id;
			planes.push_back(plane);
		}
		break;
		case 3:
		{
			shadername = "shader3" + std::to_string(System::cubes.size());
			auto cube = std::make_shared<Cube>();
			cube->init(core.get(), psos.get(), shaders.get(), texturename, shadername);
			cube->id = id;
			cubes.push_back(cube);
		}
		break;
		case 4:
		{
			shadername = "shader4" + std::to_string(System::spheres.size());
			auto sphere = std::make_shared<SphereModel>();
			sphere->init(core.get(), psos.get(), shaders.get(), texturename, shadername);
			sphere->id = id;
			spheres.push_back(sphere);
		}
		break;
		case 5:
		{
			shadername = "shader5" + std::to_string(System::smodelalphas.size());
			auto smodelalpha = std::make_shared<AlphaStaticModel>();
			smodelalpha->load(core.get(), modelname, shaders.get(), psos.get(), texturename, shadername);
			smodelalpha->id = id;
			smodelalphas.push_back(smodelalpha);
		}
		break;
		case 6:
		{
			shadername = "shader6" + std::to_string(System::anialphas.size());
			auto anialpha = std::make_shared<AlphaAnimatedModel>();
			anialpha->load(core.get(), modelname, shaders.get(), psos.get(), texturename, shadername);
			anialpha->id = id;
			anialphas.push_back(anialpha);
		}
		break;
		default:
			break;
		}
	}
	static void Init();
	static void run();
	static Vec3 GetCameraPos(std::shared_ptr<GameObject> g);
	static Vec3 GetEyePos();
	static Vec3 GetFocusPos();
	static Vec3 GetCameraUp();
	static Quaternion GetCameraRotation();
	static void Destroy(std::shared_ptr<GameObject> g);
};
inline List<std::shared_ptr<GameObject>> System::gameobjects;
inline std::vector<std::shared_ptr<Plane>> System::planes;
inline std::vector<std::shared_ptr<Cube>> System::cubes;
inline std::vector<std::shared_ptr<SphereModel>> System::spheres;
inline std::vector<std::shared_ptr<StaticModel>> System::smodels;
inline std::vector<std::shared_ptr<AnimatedModel>> System::anis;
inline std::vector<std::shared_ptr<AlphaStaticModel>> System::smodelalphas;
inline std::vector<std::shared_ptr<AlphaAnimatedModel>> System::anialphas;
inline std::vector<std::shared_ptr<AnimationInstance>> System::animatedInstances;
inline Matrix System::vp;