#pragma once
#include <iostream>
#include "Object.h"
#include "System.h"

class GameObject;
class Behavior;

class Component:public Object{
public:
	int typeID;
	int state = 0;
	std::shared_ptr<GameObject> m_GameObject;
	bool isActive=true;
public:
	Component():typeID(0),state(0){}
	void SetTypeID(){
		typeID = static_cast<int>(typeid(*this).hash_code());
	}
	void SetGameObject(std::shared_ptr<GameObject> g) {
		m_GameObject = g;
	}
	std::shared_ptr<GameObject> GetGameObject() {
		return m_GameObject;
	}
	bool operator == (Component& c) {
		if (id == c.id) {
			return true;
		}
		return false;
	}
	virtual void Awake() {};
	virtual void Start() {};
	virtual void update() {};
	virtual void lateUpdate() {};
	virtual void thirdUpdate() {};
	virtual void uiRender() {};
	virtual ~Component() = default;
};
