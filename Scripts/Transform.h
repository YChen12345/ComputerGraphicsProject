#pragma once
#include "Mathf.h"


struct Transform {
public:
	Vec3 position;
	Quaternion rotation;
	Vec3 scaling;
public:
	Transform() {
		position = Vec3(0, 0, 0);
		rotation = Quaternion(1, 0, 0, 0);
		scaling = Vec3(1, 1, 1);
	}
	void Translate(Vec3 dir) {
		position+=dir;
	}
	void Rotate(Quaternion& q) {
		rotation = rotation * q;
	}
	void FromAxisAngle(const Vec3& axis, float angle) {
		rotation=Quaternion::FromAxisAngle(axis, angle);
	}
	void rotateByEulerAngles(float tx, float ty, float tz) {
		rotation = Quaternion::rotateByEulerAngles(rotation, tx, ty, tz);
	}
	void Init() {
		position = Vec3(0, 0, 0);
		rotation = Quaternion(1, 0, 0, 0);
		scaling = Vec3(1, 1, 1);
	}
	Vec3 front() {
		return (rotation * Vec3(0, 0, 1)).Normalize();
	}
	Vec3 right() {
		return (rotation * Vec3(1, 0, 0)).Normalize();
	}
	Vec3 up() {
		return (rotation * Vec3(0, 1, 0)).Normalize();
	}
};