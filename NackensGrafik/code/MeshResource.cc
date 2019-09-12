#include "MeshResource.h"
#include "config.h"

MeshResource::MeshResource()
{

}

MeshResource::~MeshResource()
{
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ibo);
}

void MeshResource::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 5, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 5, (GLvoid*)(sizeof(float32) * 3));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*) 0);
};

void MeshResource::BindCube()
{

	GLfloat data[40] =
	{
		//A KVADRAT
		-0.2f,	0.2f,	0.2f,		// pos 0
		1,				0,			// texture 0

		-0.2f,	-0.2f,	0.2f,		// pos 1
		1,				1,			// texture 3
		
		0.2f,	-0.2f,	0.2f,		// pos 2
		0,				1,			// texture 2
		
		0.2f,	0.2f,	0.2f,		// pos 3
		0,				0,			// texture 3


		//B KVADRAT
		-0.2f,	0.2f,	-0.2f,		// pos 4
		1,				0,			// texture 4
		
		-0.2f,	-0.2f,	-0.2f,		// pos 5
		1,				1,			// texture 5
		
		0.2f,	-0.2f,	-0.2f,		// pos 6
		0,				1,			// texture 6
		
		0.2f,	0.2f,	-0.2f,		// pos 7
		0,				0			// texture 7
	};

	GLuint indicies[36] =
	{
		//Front
		0, 1, 2,
		2, 3, 0,

		//Left
		1, 0, 4,
		4, 5, 1,

		//Right
		3, 2, 6,
		6, 7, 3,

		//Bottom
		1, 5, 6,
		6, 2, 1,

		//Top
		4, 0, 3,
		3, 7, 4,

		//Back
		7, 6, 5,
		5, 4, 7
	};

	//Vertex buffer
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 40, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Index Buffer
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 36, indicies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void MeshResource::BindQuad()
{
	GLfloat data[20] =
	{
		//A KVADRAT
		-0.2f,	0.2f,	0.2f,		// pos 0
		1,				0,			// texture 0

		-0.2f,	-0.2f,	0.2f,		// pos 1
		1,				1,			// texture 3

		0.2f,	-0.2f,	0.2f,		// pos 2
		0,				1,			// texture 2

		0.2f,	0.2f,	0.2f,		// pos 3
		0,				0,			// texture 3
	};

	GLuint indicies[6] =
	{
		//Front
		0, 1, 2,
		2, 3, 0,
	};

	//Vertex buffer
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 20, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Index Buffer
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indicies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

void MeshResource::loadFromOBJ(const char* filePath)
{
	//Aggro showed me this, example from OpenGL tutorial
	objFile = fopen(filePath, "r");

	if (objFile == NULL)
	{
		cout << "No file found..." << endl;
	}

	else
	{
		int index = 0;

		while (true)
		{
			char lineHeader[128];

			int res = fscanf(objFile, "%s", lineHeader);

			if (res == EOF)
			{
				break;
			}

			if (strcmp(lineHeader, "v") == 0)
			{
				vector3D vertexInData;

				fscanf(objFile, "%f %f %f\n", &vertexInData.vecOrigin[0], &vertexInData.vecOrigin[1], &vertexInData.vecOrigin[2]);

				temp_vertices.push_back(vertexInData);
			}

			else if (strcmp(lineHeader, "vt") == 0)
			{
				vector2D uvInData;

				fscanf(objFile, "%f %f\n", &uvInData.vecOrigin[0], &uvInData.vecOrigin[1]);

				temp_uvs.push_back(uvInData);
			}

			else if (strcmp(lineHeader, "vn") == 0)
			{
				vector3D normalsInData;

				fscanf(objFile, "%f %f %f\n", &normalsInData.vecOrigin[0], &normalsInData.vecOrigin[1], &normalsInData.vecOrigin[2]);

				temp_normals.push_back(normalsInData);
			}

			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

				if (!(matches == 9 || matches == 12))
				{
					cout << "File can't be read" << endl;
					break;
				}

				Faces faceVertexList;
				int verticesPerFace = 4 - (matches % 4);

				for (int i = 0; i < verticesPerFace; i++)
				{
					FaceVertex finals;

					finals.pos = vertexIndex[i] - 1;
					finals.uv = uvIndex[i] - 1;
					finals.norm = normalIndex[i] - 1;

					faceVertexList.push_back(finals);
				}

				faces.push_back(faceVertexList);
			}

			else
			{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, objFile);
			}
		}

		//Get's rid of dupe verticies
		for(int i = 0; i < faces.size(); i++)
		{
			Face faceVertList;

			for (int j = 0; j < faces[i].size(); j++)
			{
				int pos = faces[i][j].pos;
				int uv = faces[i][j].uv;
				int norm = faces[i][j].norm;
				string key = this->FaceKey(pos, uv, norm);

				if (this->vertexMap.find(key) == this->vertexMap.end())
				{
					Vertex tempVertex;

					tempVertex.pos = temp_vertices[pos];
					tempVertex.uv = temp_uvs[uv];
					tempVertex.norm = temp_normals[norm];

					this->vertexMap[key] = this->mesh.size();
					faceVertList.verts.push_back(this->mesh.size());
					this->mesh.push_back(tempVertex);
				}

				else
				{
					faceVertList.verts.push_back(this->vertexMap[key]);
				}
			}

			this->meshFaces.push_back(faceVertList);
		}

		//Final mesh
		for (auto i = 0; i < this->meshFaces.size(); ++i)
		{
			for (auto j = 1; j < this->meshFaces[i].verts.size() - 1; ++j)
			{
				this->indices.push_back(this->meshFaces[i].verts[0]);
				this->indices.push_back(this->meshFaces[i].verts[j]);
				this->indices.push_back(this->meshFaces[i].verts[j + 1]);
			}
		}

		//Vertex Array
		glGenVertexArrays(1, &this->vao);
		glBindVertexArray(this->vao);

		//Vertex buffer
		glGenBuffers(1, &this->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(Vertex), &mesh[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 10, NULL);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float32) * 10, (GLvoid*)(sizeof(float32) * 4));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 10, (GLvoid*)(sizeof(float32) * 6));

		//Index Buffer
		glGenBuffers(1, &this->ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}
}

void MeshResource::DrawOBJ()
{
	glBindVertexArray(this->vao);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
}

//Search for dupes in vecticies
string MeshResource::FaceKey(int pos, int uv, int norm)
{
	string posS = to_string(pos);
	string uvS = to_string(pos);
	string normS = to_string(pos);

	string result = posS + uvS + normS;
	return result;
}