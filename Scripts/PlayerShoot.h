#pragma once
#include "Behavior.h"
#include "Raycast.h"

class PlayerShoot :public Behavior {
public:
	PlayerShoot() { SetTypeID(); }
	void update() override {
		auto window = System::window;
		auto timer = System::timer;
		auto role = GetGameObject();
		float dt = timer->deltaTime;		
		if (window->GetMouseButtonDown(0)) {
			if (role->GetComponent<Raycast>() != nullptr) {
				if (role->GetComponent<Raycast>()->firstHit != nullptr) {
					auto firsthit = role->GetComponent<Raycast>()->firstHit;
					if (Distance3(role->transform.position, firsthit->transform.position) < 100) {
						float r = randomRange(0, 100);
						if (r < 25) {
							firsthit->transform.position = Vec3(-52,0, randomRange(-50,50));
						}
						else if(r < 50)
						{
							firsthit->transform.position = Vec3(52, 0, randomRange(-50, 50));
						}
						else if (r < 75)
						{
							firsthit->transform.position = Vec3(randomRange(-50, 50), 0, -52);
						}
						else if (r < 101)
						{
							firsthit->transform.position = Vec3(randomRange(-50, 50), 0, 52);
						}		
					}
				}
			}		
		}
	}
};