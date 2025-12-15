#pragma once
#include "Behavior.h"
#include "Ray.h"

class Sphere {
public:
	Vec3 center;
	float radius;

	Sphere() : center(Vec3(0,0,0)), radius(0) {}
	Sphere(const Vec3& c, float r) : center(c), radius(r) {}

	void Set(Vec3& pos, float r) {
		center = pos;
		radius = r;
	}

	void Translate(Vec3& pos) {
		center = pos;
	}

	bool intersect(const Sphere& other, Vec3& normal, float& penetration) const {
		Vec3 diff = center - other.center;
		float distSq = diff.LengthSq();
		float sumRadius = radius + other.radius;

		if (distSq >= sumRadius * sumRadius) return false;

		float dist = sqrt(distSq);
		normal = diff.Normalize();
		penetration = sumRadius - dist;
		return true;
	}
};
class AABB {
public:
	Vec3 min;
	Vec3 max;

	AABB() { reset(); }

	void reset() {
		min = Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
		max = Vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}
	void extend(const Vec3& p) {
		min = Vec3::Min(min, p);
		max = Vec3::Max(max, p);
	}
	void Set(Vec3& pos,float x, float y, float z) {
		min = pos - Vec3(x / 2, y / 2, z / 2);
		max = pos + Vec3(x / 2, y / 2, z / 2);
	}
	void Translate(Vec3& pos) {
		Set(pos, (max.x - min.x), (max.y - min.y), (max.z- min.z));
	}
	bool intersect(const AABB& other, Vec3& normal, float& penetration) const {
		float overlapX = MMin(max.x, other.max.x) - MMax(min.x, other.min.x);
		float overlapY = MMin(max.y, other.max.y) - MMax(min.y, other.min.y);
		float overlapZ = MMin(max.z, other.max.z) - MMax(min.z, other.min.z);

		if (overlapX <= 0 || overlapY <= 0 || overlapZ <= 0) return false;

		float minOverlap = MMin(overlapX, overlapY, overlapZ);

		if (minOverlap == overlapX) {
			normal = (center().x < other.center().x) ? Vec3(-1, 0, 0) : Vec3(1, 0, 0);
			penetration = overlapX;
		}
		else if (minOverlap == overlapY) {
			normal = (center().y < other.center().y) ? Vec3(0, -1, 0) : Vec3(0, 1, 0);
			penetration = overlapY;
		}
		else {
			normal = (center().z < other.center().z) ? Vec3(0, 0, -1) : Vec3(0, 0, 1);
			penetration = overlapZ;
		}
		return true;
	}
	Vec3 center() const { return (min + max) * 0.5f; }
};
inline bool rayIntersectAABB(const Ray& ray, const AABB& aabb, float& tHit) {
	Vec3 t0 = (aabb.min - ray.origin) * ray.invdir;
	Vec3 t1 = (aabb.max - ray.origin) * ray.invdir;

	Vec3 tNear = Vec3::Min(t0, t1);
	Vec3 tFar = Vec3::Max(t0, t1);

	float tEnter = MMax(tNear.x, tNear.y, tNear.z);
	float tExit = MMin(tFar.x, tFar.y, tFar.z);

	tHit = tEnter;
	return (tEnter < tExit) && (tExit > 0);
}
inline bool rayIntersectSphere(const Ray& ray, const Sphere& sphere, float& tHit) {
	Vec3 oc = ray.origin - sphere.center;

	float a = Dot(ray.dir, ray.dir);
	float b = 2.0f * Dot(oc, ray.dir);
	float c = Dot(oc, oc) - sphere.radius * sphere.radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return false;

	float sqrtD = sqrt(discriminant);
	float t0 = (-b - sqrtD) / (2 * a);

	if (t0 >= 0) { tHit = t0; return true; }

	float t1 = (-b + sqrtD) / (2 * a);
	if (t1 >= 0) { tHit = t1; return true; }

	return false;
}

inline bool sphereIntersectAABB
(const Sphere& sphere, const AABB& aabb, Vec3& normal, float& penetration) {
	Vec3 closest;
	closest.x = MMax(aabb.min.x, MMin(sphere.center.x, aabb.max.x));
	closest.y = MMax(aabb.min.y, MMin(sphere.center.y, aabb.max.y));
	closest.z = MMax(aabb.min.z, MMin(sphere.center.z, aabb.max.z));

	Vec3 diff = sphere.center - closest;
	float distSq = diff.LengthSq();

	float radiusSq = sphere.radius * sphere.radius;
	if (distSq > radiusSq) return false;

	float dist = sqrt(distSq);
	if (dist > 0) {
		normal = diff.Normalize();
	}
	else
	{
		normal = Vec3(1, 0, 0);
	}
	penetration = sphere.radius - dist;
	return true;
}
class Collision :public Behavior {
public:
	int still;
	int type;
	int mode;
	Vec3 position;
	Sphere sp;
	AABB ab;

public:
	Collision(int t, float x,float y,float z,int st=0){
		SetTypeID();
		mode = 0;
		still = st;
		type = t;
		position = Vec3(0, 0, 0);
		ab.Set(position, x,y,z);
	}
	Collision(int t, float r,int st = 0) {
		SetTypeID();
		mode = 1;
		still = st;
		type = t;
		position = Vec3(0, 0, 0);
		sp.Set(position, r);
	}
	void lateUpdate() override {
		ab.Translate(GetGameObject()->transform.position);
		sp.Translate(GetGameObject()->transform.position);
		if (still == 1) {
			bool state = true;
			while (state) {
				state = false;
				if (mode == 0) {
					ab.Translate(GetGameObject()->transform.position);
					for (int i = 0; i < System::gameobjects.length; i++) {
						if (System::gameobjects[i]->m_IsActive == true && System::gameobjects[i]->m_IsDestroy == 0
							&& GetGameObject()->id != System::gameobjects[i]->id) {
							auto c = System::gameobjects[i]->GetComponent<Collision>();
							if (c != nullptr) {
								if (c->type <= type) {
									Vec3 normal;
									float p;
									if (c->mode == 0) {
										if (ab.intersect(c->ab, normal, p)) {
											GetGameObject()->transform.position += normal * p;
											ab.Translate(GetGameObject()->transform.position);
											//state = true;
											//return;
										}
									}
									else if (c->mode == 1) {
										if (sphereIntersectAABB(c->sp, ab, normal, p)) {
											GetGameObject()->transform.position -= normal * p;
											ab.Translate(GetGameObject()->transform.position);
											//state = true;
											//return;
										}
									}
								}
							}
						}
					}
				}
				else if (mode == 1)
				{
					sp.Translate(GetGameObject()->transform.position);
					for (int i = 0; i < System::gameobjects.length; i++) {
						if (System::gameobjects[i]->m_IsActive == true && System::gameobjects[i]->m_IsDestroy == 0
							&& GetGameObject()->id != System::gameobjects[i]->id) {
							auto c = System::gameobjects[i]->GetComponent<Collision>();
							if (c != nullptr) {
								if (c->type <= type) {
									Vec3 normal;
									float p;
									if (c->mode == 0) {
										if (sphereIntersectAABB(sp, c->ab, normal, p)) {
											GetGameObject()->transform.position += normal * p;
											sp.Translate(GetGameObject()->transform.position);
											//state = true;
											//return;
										}
									}
									else if (c->mode == 1) {
										if (sp.intersect(c->sp, normal, p)) {
											GetGameObject()->transform.position += normal * p;
											sp.Translate(GetGameObject()->transform.position);
											//state = true;
											//return;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
};
