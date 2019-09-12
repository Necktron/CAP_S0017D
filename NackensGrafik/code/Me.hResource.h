#pragma once
#include "core/app.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class MeshResource
{
	struct Face
	{
		vector<GLuint> verts;
	};

	public: struct Vertex
	{
		vector3D pos;
		vector2D uv;
		vector3D norm;
	};

	struct FaceVertex
	{
		int pos = 0;
		int uv = 0;
		int norm = 0;
	};

	public:
		MeshResource();
		~MeshResource();

		void Draw();
		void BindCube();
		void BindQuad();
		void loadFromOBJ(const char* filePath);
		void DrawOBJ();
		string FaceKey(int a, int b, int c);

		vector<GLuint> indices;
		vector<Vertex> mesh;

	private:
		
		//Stuff that belong to Aggro's solution
		FILE* objFile;

		vector<vector3D> temp_vertices;
		vector<vector2D> temp_uvs;
		vector<vector3D> temp_normals;

		GLuint vbo;
		GLuint vao;
		GLuint ibo;

		typedef vector<FaceVertex> Faces;
		map<string, int> vertexMap;
		vector<Face> meshFaces;
		vector<Faces> faces;
};