#include "ShaderObject.h"
#include "config.h"

ShaderObject::ShaderObject()
{

}

ShaderObject::~ShaderObject()
{

}

string ShaderObject::load(const char *filename)
{
	string output;
	string line;
	ifstream file;

	file.open(filename);
	
	if(file.is_open())
	{
		while (std::getline(file, line))
		{
			output.append(line + "\n");
		}
	}
		
	return output;
}

//load the vertex shader
void ShaderObject::LoadVertShader(const char *filename)
{
	string text = load(filename);

	GLchar *shaderReadData = (GLchar*)text.c_str();
	GLint length = strlen(shaderReadData);

	// setup vertex shader
	this->soVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->soVertexShader, 1, &shaderReadData, &length);
	glCompileShader(this->soVertexShader);

	// get error log
	glGetShaderiv(this->soVertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->soVertexShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}
}

//Load the fragment shader
void ShaderObject::LoadFragShader(const char *filename)
{
	string text = load(filename);

	GLchar *shaderReadData = (GLchar*)text.c_str();
	GLint length = strlen(shaderReadData);

	this->soPixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->soPixelShader, 1, &shaderReadData, &length);
	glCompileShader(this->soPixelShader);

	// get error log
	glGetShaderiv(this->soPixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->soPixelShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}
}

void ShaderObject::useProgram()
{
	glUseProgram(this->soProgram);
}

void ShaderObject::setupMatrix3fv(const GLchar* name, matrix3D mat)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniformMatrix4fv(uMap[temp], 1, GL_FALSE, (float*)&mat);
}

void ShaderObject::setupMatrix3fvt(const GLchar* name, matrix3D mat)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniformMatrix4fv(uMap[temp], 1, GL_TRUE, (float*)&mat);
}
void ShaderObject::setupMatrix3fv(const GLchar* name, std::vector<matrix3D> mat, GLint count)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniformMatrix4fv(uMap[temp], count, GL_TRUE, (float*)&mat[0]);
}

void ShaderObject::setupVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniform4f(uMap[temp], x, y, z, w);
}

void ShaderObject::setupVector3f(const GLchar* name, vector3D vec)
{
	GLfloat x, y, z, w;

	x = vec.vecOrigin[0];
	y = vec.vecOrigin[1];
	z = vec.vecOrigin[2];
	w = vec.vecOrigin[3];

	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniform4f(uMap[temp], x, y, z, w);

}


void ShaderObject::setupVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniform3f(uMap[temp], x, y, z);
}

void ShaderObject::setupUniformFloat(const GLchar* name, GLfloat shine)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniform1f(uMap[temp], shine);
}

void ShaderObject::setupUniformInt(const GLchar *name, GLint shine)
{
	std::string temp = name;
	if (uMap.find(temp) == uMap.end())
	{
		GLuint shaderMatrix = glGetUniformLocation(this->soProgram, name);
		uMap[temp] = shaderMatrix;
	}

	this->useProgram();
	glUniform1i(uMap[temp], shine);
}

// Link the vertex and fragment shader into a shader program
void ShaderObject::apply()
{
	// create a program object
	this->soProgram = glCreateProgram();
	glAttachShader(this->soProgram, this->soVertexShader);
	glAttachShader(this->soProgram, this->soPixelShader);
	glLinkProgram(this->soProgram);
	glGetProgramiv(this->soProgram, GL_INFO_LOG_LENGTH, &shaderLogSize);

	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->soProgram, shaderLogSize, NULL, buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}

	glUseProgram(this->soProgram);
}