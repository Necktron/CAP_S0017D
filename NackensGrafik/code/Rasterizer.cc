#include "Rasterizer.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

Rasterizer::Rasterizer()
{
	PixelColor col;
	col.r = 0;
	col.g = 0;
	col.b = 0;

	pixels.assign(width*height, col);
	zDepth.assign(width*height, 0.0f);
}

Rasterizer::~Rasterizer()
{

}

Rasterizer::Scanline::Scanline(int xOne, int xTwo, int y)
{
	if (xOne > xTwo)
	{
		xBegin = xTwo, xEnd = xOne;
	}

	else
	{
		xBegin = xOne, xEnd = xTwo;
	}

	Y = y;
}

Rasterizer::Edge::Edge(vector3D vOne, vector3D vTwo)
{
	if (vOne.vecOrigin[1] < vTwo.vecOrigin[1])
	{
		xb = vOne.vecOrigin[0];
		yb = vOne.vecOrigin[1];
		xe = vTwo.vecOrigin[0];
		ye = vTwo.vecOrigin[1];
	}

	else
	{
		xb = vTwo.vecOrigin[0];
		yb = vTwo.vecOrigin[1];
		xe = vOne.vecOrigin[0];
		ye = vOne.vecOrigin[1];
	}

	dx = (xe - xb);
	dy = (ye - yb);

	if (dx >= 0)
	{
		if (dy > dx)
		{
			oct = OctantTwo;
			std::swap(dx, dy);
		}

		else
		{
			oct = OctantOne;
		}
	}

	else
	{
		if (dy > -dx)
		{
			oct = OctantThree;
			std::swap(dx, dy);
		}

		else
		{
			oct = OctantFour;
		}
	}

	dx = abs(dx);
	dy = abs(dy);

	d = 2 * dy - dx;
	e = 2 * dy;
	ne = 2 * (dy - dx);

	x = xb;
	y = yb;
}

void Rasterizer::scanline(const Scanline &scan)
{
	int diffX = scan.xEnd - scan.xBegin;

	if (diffX == 0)
	{
		return;
	}

	for (int x = scan.xBegin; x <= scan.xEnd; x++)
	{
		float u, v, w;
		barycentric(vector2D(x, scan.Y), vector2D(vertexOne.vecOrigin[0], vertexOne.vecOrigin[1]), vector2D(vertexTwo.vecOrigin[0], vertexTwo.vecOrigin[1]), vector2D(vertexThree.vecOrigin[0], vertexThree.vecOrigin[1]), u, v, w);
		float corrW = (u * wOne + v * wTwo + w * wThree);
		float zPixel = ((vertexOne.vecOrigin[2] * u) + (vertexTwo.vecOrigin[2] * v) + (vertexThree.vecOrigin[2] * w));

		int index = (scan.Y * width + x);

		if (index < 0 || index >= (width * height))
		{
			continue;
		}

		if (zDepth[index] > zPixel)
		{
			continue;
		}

		zDepth[index] = zPixel;

		vector2D texture = ((uvOne * u) * wOne + (uvTwo * v) * wTwo + (uvThree * w) * wThree) / corrW;
		vector3D normal = ((normOne * u) * wOne + (normTwo * v) * wTwo + (normThree * w) * wThree) / corrW;
		vector3D diff = ((diffColorOne * u) * wOne + (diffColorTwo * v) * wTwo + (diffColorThree * w) * wThree) / corrW;

		PixelColor col = fragments({ texture.vecOrigin[0], 1 - texture.vecOrigin[1] }, normal, image, this->w, h, n);
		
		col.r = std::min((col.r * diff.vecOrigin[0]), 255.0f);
		col.g = std::min((col.g * diff.vecOrigin[1]), 255.0f);
		col.b = std::min((col.b * diff.vecOrigin[2]), 255.0f);

		if ((scan.Y * width + x) < 0)
		{
			continue;
		}

		else if((scan.Y * width + x) >= width * height)
		{
			continue;
		}

		if (x > 0 && x < width)
		{
			this->pixels[index] = col;
		}
	}
}

void Rasterizer::increment(Edge &edge)
{
	if (edge.oct == OctantOne)
	{
		edge.x++;

		if (edge.d < 0)
		{
			edge.d += edge.e;
		}

		else
		{
			edge.d += edge.ne;
			edge.y++;
		}
	}

	else if (edge.oct == OctantTwo)
	{
		edge.y++;
		if (edge.d < 0)
		{
			edge.d += edge.e;
		}

		else
		{
			edge.d += edge.ne;
			edge.x++;
		}
	}

	else if (edge.oct == OctantThree)
	{
		edge.y++;
		if (edge.d < 0)
		{
			edge.d += edge.e;
		}

		else
		{
			edge.d += edge.ne;
			edge.x--;
		}
	}

	else if (edge.oct == OctantFour)
	{
		edge.x--;
		if (edge.d < 0)
		{
			edge.d += edge.e;
		}

		else
		{
			edge.d += edge.ne;
			edge.y++;
		}
	}
}

std::vector<Rasterizer::PixelColor> Rasterizer::pixelRetriver()
{
	return this->pixels;
}

void Rasterizer::rasterize(vector3D vOne, vector3D vTwo, vector3D vThree)
{
	Edge edges[3] =
	{
		Edge(vOne, vTwo),
		Edge(vOne, vThree),
		Edge(vThree, vTwo)
	};

	int maxLength = 0, EdgeL = 0;

	for (int i = 0; i < 3; i++)
	{
		int length = edges[i].ye - edges[i].yb;
		if (length > maxLength)
		{
			maxLength = length;
			EdgeL = i;
		}
	}

	int EdgeOneS, EdgeTwoS;

	if (edges[(EdgeL + 1) % 3].yb > edges[(EdgeL + 2) % 3].yb)
	{
		EdgeTwoS = (EdgeL + 1) % 3;
		EdgeOneS = (EdgeL + 2) % 3;
	}

	else
	{
		EdgeOneS = (EdgeL + 1) % 3;
		EdgeTwoS = (EdgeL + 2) % 3;
	}

	while (edges[EdgeL].y < edges[EdgeL].ye)
	{
		int obsoleteY = edges[EdgeL].y;

		while (edges[EdgeL].y = obsoleteY)
		{
			increment(edges[EdgeL]);
		}

		if (edges[EdgeL].y <= edges[EdgeOneS].ye)
		{
			while (edges[EdgeL].y > edges[EdgeOneS].y)
			{
				increment(edges[EdgeOneS]);
			}

			scanline(Scanline(edges[EdgeOneS].x, edges[EdgeL].x, edges[EdgeL].y));
		}

		else
		{
			while (edges[EdgeL].y > edges[EdgeTwoS].y)
			{
				increment(edges[EdgeTwoS]);
			}

			scanline(Scanline(edges[EdgeTwoS].x, edges[EdgeL].x, edges[EdgeL].y));
		}
	}
}

void Rasterizer::barycentric(vector2D p, vector2D a, vector2D b, vector2D c, float &u, float&v, float &w)
{
	vector2D vZero = b - a;
	vector2D vOne = c - a;
	vector2D vTwo = p - a;

	float D00 = vZero.dotProd(vZero);
	float D01 = vZero.dotProd(vOne);
	float D11 = vOne.dotProd(vOne);
	float D20 = vTwo.dotProd(vZero);
	float D21 = vTwo.dotProd(vOne);
	float denom = D00 * D11 - D01 * D01;
	v = (D11 * D20 - D01 * D21) / denom;
	w = (D00 * D21 - D01 * D20) / denom;
	u = 1.0f - v - w;
}

void Rasterizer::draw(matrix3D perspectiveMatrix, matrix3D transformMatrix)
{
	meshData = this->mesh->mesh;
	indices = this->mesh->indices;

	for (int i = 0; i < indices.size(); i += 3)
	{
		vector3D vOne(meshData[indices[i]].pos.vecOrigin[0], meshData[indices[i]].pos.vecOrigin[1], meshData[indices[i]].pos.vecOrigin[2]);
		vector3D vTwo(meshData[indices[i + 1]].pos.vecOrigin[0], meshData[indices[i + 1]].pos.vecOrigin[1], meshData[indices[i + 1]].pos.vecOrigin[2]);
		vector3D vThree(meshData[indices[i + 2]].pos.vecOrigin[0], meshData[indices[i + 2]].pos.vecOrigin[1], meshData[indices[i + 2]].pos.vecOrigin[2]);

		vector2D uOne(meshData[indices[i]].uv.vecOrigin[0], meshData[indices[i]].uv.vecOrigin[1]);
		vector2D uTwo(meshData[indices[i + 1]].uv.vecOrigin[0], meshData[indices[i + 1]].uv.vecOrigin[1]);
		vector2D uThree(meshData[indices[i + 2]].uv.vecOrigin[0], meshData[indices[i + 2]].uv.vecOrigin[1]);

		vector3D nOne(meshData[indices[i]].norm.vecOrigin[0], meshData[indices[i]].norm.vecOrigin[1], meshData[indices[i]].norm.vecOrigin[2]);
		vector3D nTwo(meshData[indices[i + 1]].norm.vecOrigin[0], meshData[indices[i + 1]].norm.vecOrigin[1], meshData[indices[i + 1]].norm.vecOrigin[2]);
		vector3D nThree(meshData[indices[i + 2]].norm.vecOrigin[0], meshData[indices[i + 2]].norm.vecOrigin[1], meshData[indices[i + 2]].norm.vecOrigin[2]);

		vertexOne = perspectiveMatrix * transformMatrix * vOne;
		vertexTwo = perspectiveMatrix * transformMatrix * vTwo;
		vertexThree = perspectiveMatrix * transformMatrix * vThree;

		perspective(vertexOne, vertexTwo, vertexThree);

		uvOne = uOne;
		uvTwo = uTwo;
		uvThree = uThree;

		normOne = nOne;
		normTwo = nTwo;
		normThree = nThree;

		diffColorOne = vertShade(meshData[indices[i]].pos, meshData[indices[i]].norm, transformMatrix);
		diffColorTwo = vertShade(meshData[indices[i + 1]].pos, meshData[indices[i + 1]].norm, transformMatrix);
		diffColorThree = vertShade(meshData[indices[i + 2]].pos, meshData[indices[i + 2]].norm, transformMatrix);

		rasterize(vertexOne, vertexTwo, vertexThree);
	}
}

void Rasterizer::fragmentShade(const std::function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)>& func)
{
	this->fragments = func;
}

void Rasterizer::vertexShade(const std::function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)>& func)
{
	this->vertShade = func;
}

void Rasterizer::textureRetriver(const char* textureFile)
{
	this->image = stbi_load(textureFile, &w, &h, &n, 0);
}

void Rasterizer::perspective(vector3D &vOne, vector3D &vTwo, vector3D &vThree)
{
	wOne = 1 / vOne.vecOrigin[3];
	wTwo = 1 / vTwo.vecOrigin[3];
	wThree = 1 / vThree.vecOrigin[3];

	vOne.vecOrigin[0] = ((vOne.vecOrigin[0] * wOne + 1) / 2) * width;
	vOne.vecOrigin[1] = ((vOne.vecOrigin[1] * wOne + 1) / 2) * height;
	vOne.vecOrigin[2] = vOne.vecOrigin[2] * wOne;

	vTwo.vecOrigin[0] = ((vTwo.vecOrigin[0] * wTwo + 1) / 2) * width;
	vTwo.vecOrigin[1] = ((vTwo.vecOrigin[1] * wTwo + 1) / 2) * height;
	vTwo.vecOrigin[2] = vTwo.vecOrigin[2] * wTwo;

	vThree.vecOrigin[0] = ((vThree.vecOrigin[0] * wThree + 1) / 2) * width;
	vThree.vecOrigin[1] = ((vThree.vecOrigin[1] * wThree + 1) / 2) * height;
	vThree.vecOrigin[2] = vThree.vecOrigin[2] * wThree;
}

void Rasterizer::setMesh(std::shared_ptr<MeshResource> mesh)
{
	this->mesh = mesh;
}

void Rasterizer::flush()
{
	memset(&pixels[0], 0, sizeof(pixels[0]) * pixels.size());
	zDepth.assign(width * height, 0);
}