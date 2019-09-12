#pragma once
#include "core/app.h"
#include "Vector3D.h"
#include "Matrix3D.h"
#include <fstream>
#include <iostream>
#include <string>

#include <vector>
#include <map>

using namespace std;
class ShaderObject
{
	public:
		ShaderObject();
		~ShaderObject();

		string load(const char *filename);
		void LoadVertShader(const char *filename);
		void LoadFragShader(const char *filename);

		void useProgram();

		void setupMatrix3fv(const GLchar* name, matrix3D mat);
		void setupMatrix3fv(const GLchar* name, std::vector<matrix3D> mat, GLint count);
		void setupMatrix3fvt(const GLchar* name, matrix3D mat);
		void setupVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		void setupVector3f(const GLchar* name, vector3D vec);
		void setupVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
		void setupUniformFloat(const GLchar* name, GLfloat shine);
		void setupUniformInt(const GLchar* name, GLint shine);
		void apply();

		std::map<std::string, GLuint> uMap;

		GLuint soProgram;
		GLint length;
		GLint shaderLogSize;
		GLuint soVertexShader;
		GLuint soPixelShader;
};