#pragma once

class ObjectIDGenerator {
private:
	static int ID;
public:
	static int Generate() { return ++ID; }
};
inline int ObjectIDGenerator::ID = 0;

class Object{
public:
	int id;
public:
	Object():id(ObjectIDGenerator::Generate()){}
	virtual ~Object() {}
};