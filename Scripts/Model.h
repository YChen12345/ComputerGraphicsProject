#pragma once
#include "Core.h"
#include "Window.h"
#include "Timer.h"
#include "Mathf.h"
#include "Shaders.h"
#include "Mesh.h"
#include "PSO.h"
#include "GEMLoader.h"
#include "Animation.h"
#include "Texture.h"

// Properties -> Linker -> System -> Windows

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
class UI
{
public:
	Mesh mesh;
	std::string shaderName;
	std::string psoName;
	Texture texture;

	STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv)
	{
		STATIC_VERTEX v;
		v.pos = p;
		v.normal = n;
		ShadingFrame frame;
		frame.fromVector(n);
		v.tangent = frame.tangent;
		v.tu = tu;
		v.tv = tv;
		return v;
	}
	void init(Core* core, PSOManager* psos, Shaders* shaders, std::string texturename, std::string sname)
	{
		std::vector<STATIC_VERTEX> vertices;
		vertices.push_back(addVertex(Vec3(-1, -1, 0), Vec3(0, 0, 1), 0, 0));
		vertices.push_back(addVertex(Vec3(1, -1, 0), Vec3(0, 0, 1), 1, 0));
		vertices.push_back(addVertex(Vec3(-1, 1, 0), Vec3(0, 0, 1), 0, 1));
		vertices.push_back(addVertex(Vec3(1, 1, 0), Vec3(0, 0, 1), 1, 1));
		std::vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(1);
		indices.push_back(3);
		indices.push_back(2);
		mesh.init(core, vertices, indices);
		shaderName = sname;
		psoName = sname+"PSO";
		shaders->load(core, shaderName, "VS.txt", "PSUI.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(),false,true);
		texture.init(core, texturename);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp, Matrix& W)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &W);
		shaders->updateTexturePS(core, shaderName, "tex", texture.heapOffset);
		shaders->apply(core, shaderName);
		psos->bind(core, psoName);
		mesh.draw(core);
	}
};
class SkyBox
{
public:
	Mesh mesh;
	std::string shaderName;
	std::string psoName;
	Texture texture;

	STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv)
	{
		STATIC_VERTEX v;
		v.pos = p;
		v.normal = n;
		ShadingFrame frame;
		frame.fromVector(n);
		v.tangent = frame.tangent;
		v.tu = tu;
		v.tv = tv;
		return v;
	}
	void init(Core* core, PSOManager* psos, Shaders* shaders, std::string texturename, std::string sname)
	{
		int rings = 20;
		int segments = 20;
		float radius = 1;
		std::vector<STATIC_VERTEX> vertices;
		for (int lat = 0; lat <= rings; lat++) {
			float theta = lat * PI / rings;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);
			for (int lon = 0; lon <= segments; lon++) {
				float phi = lon * 2.0f * PI / segments;
				float sinPhi = sinf(phi);
				float cosPhi = cosf(phi);
				Vec3 position(radius * sinTheta * cosPhi, radius * cosTheta,
					radius * sinTheta * sinPhi);
				Vec3 normal = position.Normalize();
				float tu = 1.0f - (float)lon / segments;
				float tv = 1.0f - (float)lat / rings;
				vertices.push_back(addVertex(position, normal, tu, tv));
			}
		}

		std::vector<unsigned int> indices;
		for (int lat = 0; lat < rings; lat++)
		{
			for (int lon = 0; lon < segments; lon++)
			{
				int current = lat * (segments + 1) + lon;
				int next = current + segments + 1;
				indices.push_back(current);
				indices.push_back(next);
				indices.push_back(current + 1);
				indices.push_back(current + 1);
				indices.push_back(next);
				indices.push_back(next + 1);
			}
		}
		mesh.init(core, vertices, indices);
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(), false, false);
		texture.init(core, texturename);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp)
	{
		Matrix W;
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &W);
		shaders->updateTexturePS(core, shaderName, "tex", texture.heapOffset);
		shaders->apply(core, shaderName);
		psos->bind(core, psoName);
		mesh.draw(core);
	}
};

class Plane
{
public:
	int id;
	Mesh mesh;
	std::string shaderName;
	std::string psoName;
	Texture texture; 

	STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv)
	{
		STATIC_VERTEX v;
		v.pos = p;
		v.normal = n;
		ShadingFrame frame;
		frame.fromVector(n);
		v.tangent = frame.tangent;
		v.tu = tu;
		v.tv = tv;
		return v;
	}
	void init(Core* core, PSOManager* psos, Shaders* shaders, std::string texturename, std::string sname)
	{
		std::vector<STATIC_VERTEX> vertices;
		vertices.push_back(addVertex(Vec3(-1, 0, -1), Vec3(0, 1, 0), 0, 0));
		vertices.push_back(addVertex(Vec3(1, 0, -1), Vec3(0, 1, 0), 1, 0));
		vertices.push_back(addVertex(Vec3(-1, 0, 1), Vec3(0, 1, 0), 0, 1));
		vertices.push_back(addVertex(Vec3(1, 0, 1), Vec3(0, 1, 0), 1, 1));
		std::vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(1);
		indices.push_back(3);
		indices.push_back(2);
		mesh.init(core, vertices, indices);
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(),true,false);
		texture.init(core, texturename);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp, Matrix& W)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &W);
		shaders->updateTexturePS(core, shaderName, "tex", texture.heapOffset);
		shaders->apply(core, shaderName);
		psos->bind(core, psoName);
		mesh.draw(core);
	}
};

class Cube
{
public:
	int id;
	Mesh mesh;
	std::string shaderName;
	std::string psoName;
	Texture texture;

	STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv)
	{
		STATIC_VERTEX v;
		v.pos = p;
		v.normal = n;
		ShadingFrame frame;
		frame.fromVector(n);
		v.tangent = frame.tangent;
		v.tu = tu;
		v.tv = tv;
		return v;
	}
	void init(Core* core, PSOManager* psos, Shaders* shaders, std::string texturename, std::string sname)
	{
		std::vector<STATIC_VERTEX> vertices;
		Vec3 p0 = Vec3(-1.0f, -1.0f, -1.0f);
		Vec3 p1 = Vec3(1.0f, -1.0f, -1.0f);
		Vec3 p2 = Vec3(1.0f, 1.0f, -1.0f);
		Vec3 p3 = Vec3(-1.0f, 1.0f, -1.0f);
		Vec3 p4 = Vec3(-1.0f, -1.0f, 1.0f);
		Vec3 p5 = Vec3(1.0f, -1.0f, 1.0f);
		Vec3 p6 = Vec3(1.0f, 1.0f, 1.0f);
		Vec3 p7 = Vec3(-1.0f, 1.0f, 1.0f);

		vertices.push_back(addVertex(p0, Vec3(0.0f, 0.0f, -1.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p1, Vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p2, Vec3(0.0f, 0.0f, -1.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p3, Vec3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f));
		vertices.push_back(addVertex(p5, Vec3(0.0f, 0.0f, 1.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p4, Vec3(0.0f, 0.0f, 1.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p7, Vec3(0.0f, 0.0f, 1.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p6, Vec3(0.0f, 0.0f, 1.0f), 0.0f, 0.0f));
		vertices.push_back(addVertex(p4, Vec3(-1.0f, 0.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p0, Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p3, Vec3(-1.0f, 0.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p7, Vec3(-1.0f, 0.0f, 0.0f), 0.0f, 0.0f));

		vertices.push_back(addVertex(p1, Vec3(1.0f, 0.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p5, Vec3(1.0f, 0.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p6, Vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p2, Vec3(1.0f, 0.0f, 0.0f), 0.0f, 0.0f));
		vertices.push_back(addVertex(p3, Vec3(0.0f, 1.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p2, Vec3(0.0f, 1.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p6, Vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p7, Vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f));
		vertices.push_back(addVertex(p4, Vec3(0.0f, -1.0f, 0.0f), 0.0f, 1.0f));
		vertices.push_back(addVertex(p5, Vec3(0.0f, -1.0f, 0.0f), 1.0f, 1.0f));
		vertices.push_back(addVertex(p1, Vec3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f));
		vertices.push_back(addVertex(p0, Vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f));

		std::vector<unsigned int> indices;
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		indices.push_back(0); indices.push_back(2); indices.push_back(3);
		indices.push_back(4); indices.push_back(5); indices.push_back(6);
		indices.push_back(4); indices.push_back(6); indices.push_back(7);
		indices.push_back(8); indices.push_back(9); indices.push_back(10);
		indices.push_back(8); indices.push_back(10); indices.push_back(11);
		indices.push_back(12); indices.push_back(13); indices.push_back(14);
		indices.push_back(12); indices.push_back(14); indices.push_back(15);
		indices.push_back(16); indices.push_back(17); indices.push_back(18);
		indices.push_back(16); indices.push_back(18); indices.push_back(19);
		indices.push_back(20); indices.push_back(21); indices.push_back(22);
		indices.push_back(20); indices.push_back(22); indices.push_back(23);

		mesh.init(core, vertices, indices);
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(), true, false);
		texture.init(core, texturename);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp, Matrix& W)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &W);
		shaders->updateTexturePS(core, shaderName, "tex", texture.heapOffset);
		shaders->apply(core, shaderName);
		psos->bind(core, psoName);
		mesh.draw(core);
	}
};

class SphereModel
{
public:
	int id;
	Mesh mesh;
	std::string shaderName;
	std::string psoName;
	Texture texture;

	STATIC_VERTEX addVertex(Vec3 p, Vec3 n, float tu, float tv)
	{
		STATIC_VERTEX v;
		v.pos = p;
		v.normal = n;
		ShadingFrame frame;
		frame.fromVector(n);
		v.tangent = frame.tangent;
		v.tu = tu;
		v.tv = tv;
		return v;
	}
	void init(Core* core, PSOManager* psos, Shaders* shaders, std::string texturename, std::string sname)
	{
		int rings = 20;
		int segments = 20;
		float radius = 1;
		std::vector<STATIC_VERTEX> vertices;
		for (int lat = 0; lat <= rings; lat++) {
			float theta = lat * PI / rings;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);
			for (int lon = 0; lon <= segments; lon++) {
				float phi = lon * 2.0f * PI / segments;
				float sinPhi = sinf(phi);
				float cosPhi = cosf(phi);
				Vec3 position(radius * sinTheta * cosPhi, radius * cosTheta,
					radius * sinTheta * sinPhi);
				Vec3 normal = position.Normalize();
				float tu = 1.0f - (float)lon / segments;
				float tv = 1.0f - (float)lat / rings;
				vertices.push_back(addVertex(position, normal, tu, tv));
			}
		}

		std::vector<unsigned int> indices;
		for (int lat = 0; lat < rings; lat++)
		{
			for (int lon = 0; lon < segments; lon++)
			{
				int current = lat * (segments + 1) + lon;
				int next = current + segments + 1;
				indices.push_back(current);
				indices.push_back(next);
				indices.push_back(current + 1);
				indices.push_back(current + 1);
				indices.push_back(next);
				indices.push_back(next + 1);
			}
		}

		mesh.init(core, vertices, indices);
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(), true, false);
		texture.init(core, texturename);
	}
	void init(Core* core, PSOManager* psos, Shaders* shaders,int rings, int segments,float radius, std::string texturename, std::string sname)
	{
		std::vector<STATIC_VERTEX> vertices;
		for (int lat = 0; lat <= rings; lat++) {
			float theta = lat * PI / rings;
			float sinTheta = sinf(theta);
			float cosTheta = cosf(theta);
			for (int lon = 0; lon <= segments; lon++) {
				float phi = lon * 2.0f * PI / segments;
				float sinPhi = sinf(phi);
				float cosPhi = cosf(phi);
				Vec3 position(radius * sinTheta * cosPhi, radius * cosTheta,
					radius * sinTheta * sinPhi);
				Vec3 normal = position.Normalize();
				float tu = 1.0f - (float)lon / segments;
				float tv = 1.0f - (float)lat / rings;
				vertices.push_back(addVertex(position, normal, tu, tv));
			}
		}

		std::vector<unsigned int> indices;
		for (int lat = 0; lat < rings; lat++)
		{
			for (int lon = 0; lon < segments; lon++)
			{
				int current = lat * (segments + 1) + lon;
				int next = current + segments + 1;
				indices.push_back(current);
				indices.push_back(next);
				indices.push_back(current + 1);
				indices.push_back(current + 1);
				indices.push_back(next);
				indices.push_back(next + 1);
			}
		}

		mesh.init(core, vertices, indices);
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(), true, false);
		texture.init(core, texturename);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp, Matrix& W)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &W);
		shaders->updateTexturePS(core, shaderName, "tex", texture.heapOffset);
		shaders->apply(core, shaderName);
		psos->bind(core, psoName);
		mesh.draw(core);
	}
};

class StaticModel
{
public:
	int id;
	std::vector<Mesh*> meshes;
	std::vector<std::string> textureFilenames;
	std::vector<Texture> textures;
	std::string shaderName;
	std::string psoName;

	void load(Core* core, std::string filename, Shaders* shaders, PSOManager* psos, std::string texturename, std::string sname)
	{
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		loader.load(filename, gemmeshes);
		for (int i = 0; i < gemmeshes.size(); i++)
		{
			Mesh* mesh = new Mesh();
			std::vector<STATIC_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesStatic.size(); j++)
			{
				STATIC_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesStatic[j], sizeof(STATIC_VERTEX));
				vertices.push_back(v);
			}
			mesh->init(core, vertices, gemmeshes[i].indices);
			meshes.push_back(mesh);
			//
			// ---------- 2. mesh to albedo ----------
			std::string texName = gemmeshes[i].material.find("albedo").getValue("");
			texName = texturename;
			textureFilenames.push_back(texName);
			textures.emplace_back();
			textures.back().init(core, texName);
		}
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(), true, false);
	}
	void updateWorld(Shaders* shaders, Matrix& w)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &w);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		psos->bind(core, psoName);
		for (int i = 0; i < meshes.size(); i++)
		{
			shaders->updateTexturePS(core, shaderName, "tex", textures[i].heapOffset);
			shaders->apply(core, shaderName);
			meshes[i]->draw(core);
		}
	}
};

class AnimatedModel
{
public:
	int id;
	std::vector<Mesh*> meshes;
	Animation animation;
	std::vector<std::string> textureFilenames;
	std::vector<Texture> textures;
	std::string shaderName;
	std::string psoName;

	void load(Core* core, std::string filename, Shaders* shaders, PSOManager* psos, std::string texturename, std::string sname)
	{
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		GEMLoader::GEMAnimation gemanimation;
		loader.load(filename, gemmeshes, gemanimation);
		for (int i = 0; i < gemmeshes.size(); i++)
		{
			Mesh* mesh = new Mesh();
			std::vector<ANIMATED_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesAnimated.size(); j++)
			{
				ANIMATED_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesAnimated[j], sizeof(ANIMATED_VERTEX));
				vertices.push_back(v);
			}
			mesh->init(core, vertices, gemmeshes[i].indices);
			meshes.push_back(mesh);
			// ------- mesh to albedo -------
			std::string texName = gemmeshes[i].material.find("albedo").getValue("");
			texName = texturename;
			textureFilenames.push_back(texName);
			textures.emplace_back();
			textures.back().init(core, texName);
		}
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VSAnim.txt", "PSAnim.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getAnimatedLayout(), true, false);
		memcpy(&animation.skeleton.globalInverse, &gemanimation.globalInverse, 16 * sizeof(float));
		for (int i = 0; i < gemanimation.bones.size(); i++)
		{
			Bone bone;
			bone.name = gemanimation.bones[i].name;
			memcpy(&bone.offset, &gemanimation.bones[i].offset, 16 * sizeof(float));
			bone.parentIndex = gemanimation.bones[i].parentIndex;
			animation.skeleton.bones.push_back(bone);
		}
		for (int i = 0; i < gemanimation.animations.size(); i++)
		{
			std::string name = gemanimation.animations[i].name;
			AnimationSequence aseq;
			aseq.ticksPerSecond = gemanimation.animations[i].ticksPerSecond;
			for (int j = 0; j < gemanimation.animations[i].frames.size(); j++)
			{
				AnimationFrame frame;
				for (int index = 0; index < gemanimation.animations[i].frames[j].positions.size(); index++)
				{
					Vec3 p;
					Quaternion q;
					Vec3 s;
					memcpy(&p, &gemanimation.animations[i].frames[j].positions[index], sizeof(Vec3));
					frame.positions.push_back(p);
					memcpy(&q, &gemanimation.animations[i].frames[j].rotations[index], sizeof(Quaternion));
					frame.rotations.push_back(q);
					memcpy(&s, &gemanimation.animations[i].frames[j].scales[index], sizeof(Vec3));
					frame.scales.push_back(s);
				}
				aseq.frames.push_back(frame);
			}
			animation.animations.insert({ name, aseq });
		}
	}
	void updateWorld(Shaders* shaders, Matrix& w)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &w);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, AnimationInstance* instance, Matrix& vp, Matrix& w)
	{
	
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &w);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "bones", instance->matrices);
		psos->bind(core, psoName);

		for (int i = 0; i < meshes.size(); i++)
		{
			shaders->updateTexturePS(core, shaderName, "tex", textures[i].heapOffset);
			shaders->apply(core, shaderName);
			meshes[i]->draw(core);
		}
	}
};
class AlphaStaticModel {
public:
	int id;
	std::vector<Mesh*> meshes;
	std::vector<std::string> textureFilenames;
	std::vector<Texture> textures;
	std::string shaderName;
	std::string psoName;

	void load(Core* core, std::string filename, Shaders* shaders, PSOManager* psos, std::string texturename, std::string sname)
	{
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		loader.load(filename, gemmeshes);
		for (int i = 0; i < gemmeshes.size(); i++)
		{
			Mesh* mesh = new Mesh();
			std::vector<STATIC_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesStatic.size(); j++)
			{
				STATIC_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesStatic[j], sizeof(STATIC_VERTEX));
				vertices.push_back(v);
			}
			mesh->init(core, vertices, gemmeshes[i].indices);
			meshes.push_back(mesh);
			//
			// ---------- 2. mesh to albedo ----------
			std::string texName = gemmeshes[i].material.find("albedo").getValue("");
			texName = texturename;
			textureFilenames.push_back(texName);
			textures.emplace_back();
			textures.back().init(core, texName);
		}
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VS.txt", "PS.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getStaticLayout(), true, true);
	}
	void updateWorld(Shaders* shaders, Matrix& w)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &w);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, Matrix& vp)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		psos->bind(core, psoName);
		for (int i = 0; i < meshes.size(); i++)
		{
			shaders->updateTexturePS(core, shaderName, "tex", textures[i].heapOffset);
			shaders->apply(core, shaderName);
			meshes[i]->draw(core);
		}
	}
};
class AlphaAnimatedModel
{
public:
	int id;
	std::vector<Mesh*> meshes;
	Animation animation;
	std::vector<std::string> textureFilenames;
	std::vector<Texture> textures;
	std::string shaderName;
	std::string psoName;

	void load(Core* core, std::string filename, Shaders* shaders, PSOManager* psos, std::string texturename, std::string sname)
	{
		GEMLoader::GEMModelLoader loader;
		std::vector<GEMLoader::GEMMesh> gemmeshes;
		GEMLoader::GEMAnimation gemanimation;
		loader.load(filename, gemmeshes, gemanimation);
		for (int i = 0; i < gemmeshes.size(); i++)
		{
			Mesh* mesh = new Mesh();
			std::vector<ANIMATED_VERTEX> vertices;
			for (int j = 0; j < gemmeshes[i].verticesAnimated.size(); j++)
			{
				ANIMATED_VERTEX v;
				memcpy(&v, &gemmeshes[i].verticesAnimated[j], sizeof(ANIMATED_VERTEX));
				vertices.push_back(v);
			}
			mesh->init(core, vertices, gemmeshes[i].indices);
			meshes.push_back(mesh);
			// ------- mesh to albedo -------
			std::string texName = gemmeshes[i].material.find("albedo").getValue("");
			texName = texturename;
			textureFilenames.push_back(texName);
			textures.emplace_back();
			textures.back().init(core, texName);
		}
		shaderName = sname;
		psoName = sname + "PSO";
		shaders->load(core, shaderName, "VSAnim.txt", "PSAnim.txt");
		psos->createPSO(core, psoName, shaders->find(shaderName)->vs, shaders->find(shaderName)->ps, VertexLayoutCache::getAnimatedLayout(), true, true);
		memcpy(&animation.skeleton.globalInverse, &gemanimation.globalInverse, 16 * sizeof(float));
		for (int i = 0; i < gemanimation.bones.size(); i++)
		{
			Bone bone;
			bone.name = gemanimation.bones[i].name;
			memcpy(&bone.offset, &gemanimation.bones[i].offset, 16 * sizeof(float));
			bone.parentIndex = gemanimation.bones[i].parentIndex;
			animation.skeleton.bones.push_back(bone);
		}
		for (int i = 0; i < gemanimation.animations.size(); i++)
		{
			std::string name = gemanimation.animations[i].name;
			AnimationSequence aseq;
			aseq.ticksPerSecond = gemanimation.animations[i].ticksPerSecond;
			for (int j = 0; j < gemanimation.animations[i].frames.size(); j++)
			{
				AnimationFrame frame;
				for (int index = 0; index < gemanimation.animations[i].frames[j].positions.size(); index++)
				{
					Vec3 p;
					Quaternion q;
					Vec3 s;
					memcpy(&p, &gemanimation.animations[i].frames[j].positions[index], sizeof(Vec3));
					frame.positions.push_back(p);
					memcpy(&q, &gemanimation.animations[i].frames[j].rotations[index], sizeof(Quaternion));
					frame.rotations.push_back(q);
					memcpy(&s, &gemanimation.animations[i].frames[j].scales[index], sizeof(Vec3));
					frame.scales.push_back(s);
				}
				aseq.frames.push_back(frame);
			}
			animation.animations.insert({ name, aseq });
		}
	}
	void updateWorld(Shaders* shaders, Matrix& w)
	{
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &w);
	}
	void draw(Core* core, PSOManager* psos, Shaders* shaders, AnimationInstance* instance, Matrix& vp, Matrix& w)
	{

		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "W", &w);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "VP", &vp);
		shaders->updateConstantVS(shaderName, "staticMeshBuffer", "bones", instance->matrices);
		psos->bind(core, psoName);

		for (int i = 0; i < meshes.size(); i++)
		{
			shaders->updateTexturePS(core, shaderName, "tex", textures[i].heapOffset);
			shaders->apply(core, shaderName);
			meshes[i]->draw(core);
		}
	}
};