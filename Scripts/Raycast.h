#pragma once
#include "Behavior.h"
#include "Collision.h"
#include "Ray.h"

class Raycast : public Behavior{
public:
	int type;
	Vec3 position;
	Vec3 dir;
	Ray ray;
	List<std::shared_ptr<GameObject>> hitList;
	std::shared_ptr<GameObject> firstHit;
public:
	Raycast(int t=0) {
		SetTypeID();
		type = t;
		position = Vec3(0, 0, 0);
	}
	void lateUpdate() override {
		position = GetGameObject()->transform.position;
		dir = GetGameObject()->transform.front();
		ray.init(position, dir);
		hitList.Clear();
		firstHit = nullptr;
		float minthit=10000.f;
		float thit=0.f;
		for (int i = 0; i < System::gameobjects.length; i++) {
			if (System::gameobjects[i]->m_IsActive == true && System::gameobjects[i]->m_IsDestroy == 0
				&& GetGameObject()->id != System::gameobjects[i]->id) {
				auto c = System::gameobjects[i]->GetComponent<Collision>();
				if (c != nullptr) {
					if (c->type == type) {					
						if (c->mode == 0) {
							if (rayIntersectAABB(ray,c->ab,thit)) {
								hitList.Add(System::gameobjects[i]);
								if (thit < minthit) {
									minthit = thit;
									firstHit = System::gameobjects[i];
								}
								
							}
						}
						else if (c->mode == 1) {
							if (rayIntersectSphere(ray, c->sp, thit)) {
								hitList.Add(System::gameobjects[i]);
								if (thit < minthit) {
									minthit = thit;
									firstHit = System::gameobjects[i];
								}
							}
						}
					}
				}
			}
		}
	}
};