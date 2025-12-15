#pragma once
#include "Mathf.h"
class Ray {
public:
	Vec3 origin;
	Vec3 dir;
	Vec3 invdir;

	Ray() {}
	Ray(const Vec3& o, const Vec3& d) { init(o, d); }

	void init(const Vec3& o, const Vec3& d) {
		origin = o;
		dir = d;
		invdir = Vec3(1.0f / d.x, 1.0f / d.y, 1.0f / d.z);
	}

	Vec3 at(float t) const {
		return origin + dir * t;
	}
};