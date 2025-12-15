#pragma once
#include "System.h"
#include "Transform.h"
#include "Component.h"
#include "Object.h"
#include "List.h"
#include <cmath>

class GameObject :public Object, public std::enable_shared_from_this<GameObject> {
public:                     
	bool m_IsActive;      
	int m_IsDestroy;
	Transform transform;        
	List<std::shared_ptr<Component>> components;
public:
	GameObject() {
		transform.Init();
		m_IsActive = true;
		m_IsDestroy = 0;
	}

	bool operator == (GameObject& gameobject) {
		if (id == gameobject.id) {
			return true;
		}
		return false;
	}
	
	void AddComponent(std::shared_ptr<Component> c) {
		c->SetGameObject(shared_from_this());
		components.Add(c);
	}
	template <typename T>
	std::shared_ptr<T> GetComponent() {
		for (int i = 0; i < components.length; i++) {
			if (components[i]->typeID == static_cast<int>(typeid(T).hash_code())) {
				return std::dynamic_pointer_cast<T>(components[i]);
			}
		}
		return nullptr;
	}
	template <typename T>
	void RemoveComponent() {
		for (int i = 0; i < components.length; i++) {
			if (components[i]->typeID = static_cast<int>(typeid(T).hash_code())) {
				components.RemoveAt(i);
				return;
			}
		}
	}
	static std::shared_ptr<GameObject> Create() {
		auto g = std::make_shared<GameObject>();
		System::NewGameObject(g);
		return g;
	}
};
inline void System::Init() {
	mainCamera = GameObject::Create();
	player = GameObject::Create();
	window = std::make_shared<Window>();
	window->create(WIDTH, HEIGHT, "PokeBall");
	core = std::make_shared<Core>();
	core->init(window->hwnd, WIDTH, HEIGHT);
	shaders = std::make_shared<Shaders>();
	psos = std::make_shared<PSOManager>();
	timer = std::make_shared<Timer>();
	skybox = std::make_shared<SkyBox>();
	skybox->init(core.get(), psos.get(), shaders.get(), "Textures/sky.png", "skybox");
	Matrix p = Matrix::perspective(0.01f, 10000.0f, 1920.0f / 1080.0f, 60.0f);
	Matrix v = Matrix::lookAt(Vec3(0, 0, -1), Vec3(0, 0, 0), Vec3(0, 1, 0));
	vp = v * p;
}
inline void System::run() {
	timer->dt();
	core->beginRenderPass();
	skybox->draw(core.get(), psos.get(), shaders.get(),vp);
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->state == 0 && gameobjects[i]->components[j]->isActive) {
					gameobjects[i]->components[j]->Awake();
				}
			}
		}
	}
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->state == 1 && gameobjects[i]->components[j]->isActive) {
					gameobjects[i]->components[j]->Start();
				}
			}
		}
	}
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->state >= 2&& gameobjects[i]->components[j]->isActive) {
					gameobjects[i]->components[j]->update();
				}
			}
		}
	}
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->state >= 2 && gameobjects[i]->components[j]->isActive) {
					gameobjects[i]->components[j]->lateUpdate();
				}
			}
		}
	}
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->state >= 2 && gameobjects[i]->components[j]->isActive) {
					gameobjects[i]->components[j]->thirdUpdate();
				}
			}
		}
	}
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->isActive) {
					gameobjects[i]->components[j]->uiRender();
				}
			}
		}
	}
	for (int i = 0; i < gameobjects.length; i++) {
		if (gameobjects[i]->m_IsActive == true && gameobjects[i]->m_IsDestroy == 0) {
			for (int j = 0; j < gameobjects[i]->components.length; j++) {
				if (gameobjects[i]->components[j]->state < 2) {
					gameobjects[i]->components[j]->state++;
				}
			}
		}
	}
	bool state = true;
	while (state)
	{
		state = false;
		for (int i = 0; i < gameobjects.length; i++) {
			if (gameobjects[i]->m_IsDestroy == 1) {
				gameobjects.Remove(gameobjects[i]);
				state = true;
				break;
			}
		}
	}
}
inline void System::Destroy(std::shared_ptr<GameObject> g) {
	g->m_IsDestroy = 1;
}

inline Vec3 System::GetCameraPos(std::shared_ptr<GameObject> g) {
	if (mainCamera == nullptr) {
		return g->transform.position;
	}
	else
	{
		return (g->transform.position - mainCamera->transform.position);
	}
}
inline Vec3 System::GetEyePos() {
	return mainCamera->transform.position;
}
inline Vec3 System::GetFocusPos() {
	return (mainCamera->transform.position + mainCamera->transform.front());
}
inline Vec3 System::GetCameraUp() {
	return mainCamera->transform.up();
}
inline Quaternion System::GetCameraRotation() {
	return mainCamera->transform.rotation;
}
