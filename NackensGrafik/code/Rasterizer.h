#pragma once
#include "core/app.h"
#include "stb_image.h"
#include "Matrix3D.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "MeshResource.h"
#include <functional>
#include <vector>
#include <memory>

class Rasterizer
{
	public:
		Rasterizer();
		~Rasterizer();

		const int height = 256;
		const int width = 256;

		enum Octant
		{
			OctantOne,
			OctantTwo,
			OctantThree,
			OctantFour
		};

		struct PixelColor
		{
			unsigned char r = 0;
			unsigned char g = 0;
			unsigned char b = 0;
		};

		class Scanline
		{
		public:
			Scanline(int xOne, int xTwo, int y);
			int xBegin, xEnd, Y;
		};

		class Edge
		{
		public:
			Edge(vector3D vOne, vector3D vTwo);

			Octant oct;
			int x, y, xb, xe, yb, ye, d, dy, dx, e, ne;
		};

		std::vector<Rasterizer::PixelColor> pixelRetriver();

		//Scanline function
		void scanline(const Scanline &scan);

		void increment(Edge &edge);

		void rasterize(vector3D vOne, vector3D v2, vector3D v3);

		void barycentric(vector2D p, vector2D a, vector2D b, vector2D c, float &u, float &v, float &w);

		//Draw the rasterized mesh
		void draw(matrix3D, matrix3D);

		//Fragment Lambda function
		void fragmentShade(const std::function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)>& func);

		void vertexShade(const std::function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)>& func);

		void textureRetriver(const char* textureFile);

		void perspective(vector3D&, vector3D&, vector3D&);

		void setMesh(std::shared_ptr<MeshResource> mesh);

		//Clear pixels
		void flush();

	private:
		int leftY, rightY, bottomY, leftX, rightX, bottomX;
		vector3D vertexOne, vertexTwo, vertexThree;
		vector2D uvOne, uvTwo, uvThree;
		vector3D normOne, normTwo, normThree;
		vector3D diffColorOne, diffColorTwo, diffColorThree;
		std::vector<PixelColor> pixels;
		std::vector<MeshResource::Vertex> meshData;
		std::vector<GLuint> indices;
		std::shared_ptr<MeshResource> mesh;

		std::function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)> fragments;
		std::function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)> vertShade;

		std::vector<float> zDepth;
		int w, h, n;
		float wOne, wTwo, wThree;
		unsigned char* image;
};