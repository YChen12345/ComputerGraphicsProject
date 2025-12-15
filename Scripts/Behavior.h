#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Mathf.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

class GameObject;

class Behavior:public Component {
public:
	virtual void Awake() override {};
	virtual void Start() override {};
	virtual void update() override {};
	virtual void lateUpdate() override {};
	virtual void thirdUpdate() override {};
	virtual void uiRender() override {};
	virtual ~Behavior() = default;
};
