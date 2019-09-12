#pragma once
#include <iostream>
#include "math.h"

using namespace std;

class vector3D
{
	public:
		//Basic constructor
		vector3D();
		vector3D(float, float, float);

		//Copy constructor
		vector3D(const vector3D &other);

		//Destructor
		~vector3D();

		//Main vector that you play around with
		float vecOrigin[4];

		//Operators
		float operator* (const vector3D &other);
		vector3D operator*(float);
		vector3D operator/(float);
		vector3D operator+(vector3D other);
		vector3D operator-(vector3D other);
		vector3D operator=(vector3D &other);
		bool operator==(vector3D &other);
		bool operator!=(vector3D &other);
		float operator[](int pos);

		//Functions
		vector3D vecAdd(vector3D &other);
		vector3D vecSub(vector3D &other);
		vector3D crossProd(vector3D &other);
		float dotProd(vector3D &other);
		float vecLength();
		vector3D vecNormilisation();
		float vecGet(int i);
		void vecSet(float x, float y, float z);

		//3D exclusive
		vector3D vecScale(float scalar);
};

//Empty Constructor
inline vector3D::vector3D()
{
	vecOrigin[0] = 0;
	vecOrigin[1] = 0;
	vecOrigin[2] = 0;
	vecOrigin[3] = 1;
}

//Constructor with components
inline vector3D::vector3D(float a, float b, float c)
{
	vecOrigin[0] = a;
	vecOrigin[1] = b;
	vecOrigin[2] = c;
	vecOrigin[3] = 1;
}

//Copy Constructor
inline vector3D::vector3D(const vector3D &other)
{
	for (int i = 0; i < 4; ++i)
	{
		vecOrigin[i] = other.vecOrigin[i];
	}
}

//Destructor         
inline vector3D::~vector3D()
{

}

//Addition - Instance vector added with the sent vector
inline vector3D vector3D::vecAdd(vector3D &other)
{
	vector3D add(0, 0, 0);

	add.vecOrigin[0] = other.vecOrigin[0] + vecOrigin[0];
	add.vecOrigin[1] = other.vecOrigin[1] + vecOrigin[1];
	add.vecOrigin[2] = other.vecOrigin[2] + vecOrigin[2];

	return add;
}

//Subtraction - Instance vector minus the sent vector
inline vector3D vector3D::vecSub(vector3D &other)
{
	vector3D sub(0, 0, 0);

	sub.vecOrigin[0] = vecOrigin[0] - other.vecOrigin[0];
	sub.vecOrigin[1] = vecOrigin[1] - other.vecOrigin[1];
	sub.vecOrigin[2] = vecOrigin[2] - other.vecOrigin[2];

	return sub;
}

//Cross Product
inline vector3D vector3D::crossProd(vector3D &other)
{
	vector3D crossProduct(0, 0, 0);

	crossProduct.vecOrigin[0] = (other.vecOrigin[2] * vecOrigin[1] - other.vecOrigin[1] * vecOrigin[2]);
	crossProduct.vecOrigin[1] = (other.vecOrigin[0] * vecOrigin[2] - other.vecOrigin[2] * vecOrigin[0]);
	crossProduct.vecOrigin[2] = (other.vecOrigin[1] * vecOrigin[0] - other.vecOrigin[0] * vecOrigin[1]);

	return crossProduct;
}

//Dot Product
inline float vector3D::dotProd(vector3D &other)
{
	float dotProduct = 0;

	dotProduct = other.vecOrigin[0] * vecOrigin[0] + other.vecOrigin[1] * vecOrigin[1] + other.vecOrigin[2] * vecOrigin[2];

	return dotProduct;
}

//Length
inline float vector3D::vecLength()
{
	float length = sqrt((vecOrigin[0] * vecOrigin[0]) + (vecOrigin[1] * vecOrigin[1]) + (vecOrigin[2] * vecOrigin[2]));
	return length;
}

//Normalisering
inline vector3D vector3D::vecNormilisation()
{
	vector3D norm(0, 0, 0);

	float length = sqrt((vecOrigin[0] * vecOrigin[0]) + (vecOrigin[1] * vecOrigin[1]) + (vecOrigin[2] * vecOrigin[2]));
	float normX = (vecOrigin[0] / length);
	float normY = (vecOrigin[1] / length);
	float normZ = (vecOrigin[2] / length);

	norm.vecOrigin[0] = normX;
	norm.vecOrigin[1] = normY;
	norm.vecOrigin[2] = normZ;

	return norm;
}

//Scaling, vector * a scalar
inline vector3D vector3D::vecScale(float scalar)
{
	vector3D scaled(0, 0, 0);

	scaled.vecOrigin[0] = (vecOrigin[0] * scalar);
	scaled.vecOrigin[1] = (vecOrigin[1] * scalar);
	scaled.vecOrigin[2] = (vecOrigin[2] * scalar);

	return scaled;
}

//Get
inline float vector3D::vecGet(int i)
{
	if (i >= 3)
	{
		cout << "Error! Index out of range, max value is 2" << endl;
		return 0;
	}

	else
	{
		return vecOrigin[i];
	}
}

//Set
inline void vector3D::vecSet(float x, float y, float z)
{
	this->vecOrigin[0] = x;
	this->vecOrigin[1] = y;
	this->vecOrigin[2] = z;
}

//Operator *
inline float vector3D::operator*(const vector3D &other)
{
	return(this->vecOrigin[0] * other.vecOrigin[0]) + (this->vecOrigin[1] * other.vecOrigin[1]) + (this->vecOrigin[2] * other.vecOrigin[2]);
}

//Operator *
inline vector3D vector3D::operator*(float x)
{
	this->vecOrigin[0] *= x;
	this->vecOrigin[1] *= x;
	this->vecOrigin[2] *= x;
	return *this;
}

//Operator *
inline vector3D vector3D::operator/(float x)
{
	this->vecOrigin[0] /= x;
	this->vecOrigin[1] /= x;
	this->vecOrigin[2] /= x;
	return *this;
}

//Operator +
inline vector3D vector3D::operator+(vector3D other)
{
	vector3D addOp(0, 0, 0);

	addOp.vecOrigin[0] = vecOrigin[0] + other.vecOrigin[0];
	addOp.vecOrigin[1] = vecOrigin[1] + other.vecOrigin[1];
	addOp.vecOrigin[2] = vecOrigin[2] + other.vecOrigin[2];

	return addOp;
}

//Operator -
inline vector3D vector3D::operator-(vector3D other)
{
	vector3D subOp(0, 0, 0);

	subOp.vecOrigin[0] = vecOrigin[0] - other.vecOrigin[0];
	subOp.vecOrigin[1] = vecOrigin[1] - other.vecOrigin[1];
	subOp.vecOrigin[2] = vecOrigin[2] - other.vecOrigin[2];

	return subOp;
}

//Operator ==
inline bool vector3D::operator==(vector3D &other)
{
	return vecOrigin[0] == other.vecOrigin[0] && vecOrigin[1] == other.vecOrigin[1] && vecOrigin[2] == other.vecOrigin[2];
}

//Operator !=
inline bool vector3D::operator!=(vector3D &other)
{
	return vecOrigin[0] != other.vecOrigin[0] && vecOrigin[1] != other.vecOrigin[1] && vecOrigin[2] != other.vecOrigin[2];
}

//Operator =
inline vector3D vector3D::operator=( vector3D &other)
{
	for (int i = 0; i < 4; ++i)
		vecOrigin[i] = other.vecOrigin[i];
	return *this;
}

inline float vector3D::operator[](int pos)
{
	return vecOrigin[pos];
}