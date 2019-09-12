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
		vector3D(float, float, float, float);

		//Copy constructor
		vector3D(const vector3D &other);

		//Destructor
		~vector3D();

		//Operators
		vector3D operator*(const vector3D &other);
		vector3D operator*(const float);
		const vector3D operator*(float) const;
		vector3D operator/(const float);
		vector3D operator+(const vector3D other);
		vector3D operator-(const vector3D other) const;
		vector3D operator=(const vector3D &other);
		bool operator==(const vector3D &other);
		bool operator!=(const vector3D &other);
		float& operator[](int pos);
		const float& operator[](int pos) const;

		//Functions
		vector3D vecAdd(vector3D &other);
		vector3D vecSub(vector3D &other);
		vector3D crossProd(vector3D &other);
		float vecLength();
		vector3D vecNormilisation();
		float vecGet(int i);
		void vecSet(float x, float y, float z);
		void vecSetQuat(float x, float y, float z, float w);

		//3D exclusive
		vector3D vecScale(float scalar);

		//Extra functions for RayTrace
		vector3D& operator+=(const vector3D &v2);
		vector3D& operator-=(const vector3D &v2);
		vector3D& operator*=(const float t);
		vector3D& operator*=(const vector3D &v2);
		vector3D& operator/=(const float t);
		vector3D& operator/=(const vector3D &v2);
		inline float squared_length() const { return vecOrigin[0] * vecOrigin[0] + vecOrigin[1] * vecOrigin[1] + vecOrigin[2] * vecOrigin[2]; }

	private:
		//Main vector that you play around with
		float vecOrigin[4];
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

//Constructor with components
inline vector3D::vector3D(float a, float b, float c, float d)
{
	vecOrigin[0] = a;
	vecOrigin[1] = b;
	vecOrigin[2] = c;
	vecOrigin[3] = d;
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
inline vector3D crossProd(vector3D const &v1, vector3D const &v2)
{
	return vector3D((v1[1] * v2[2] - v1[2] * v2[1]),
	 				(-(v1[0] * v2[2] - v1[2] * v2[0])),
					(v1[0] * v2[1] - v1[1] * v2[0]));
}

//Dot Product
inline float dotProd(vector3D const &v1, vector3D const &v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

//Length
inline float vector3D::vecLength()
{
	return sqrt(vecOrigin[0] * vecOrigin[0] + vecOrigin[1] * vecOrigin[1] + vecOrigin[2] * vecOrigin[2]);
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

//Set
inline void vector3D::vecSetQuat(float x, float y, float z, float w)
{
	this->vecOrigin[0] = x;
	this->vecOrigin[1] = y;
	this->vecOrigin[2] = z;
	this->vecOrigin[3] = w;
}

//Operator *
inline vector3D vector3D::operator*(const vector3D &other)
{
	return vector3D(vecOrigin[0] * other[0], vecOrigin[1] * other[1], vecOrigin[2] * other[2]);
}

//Operator *
inline const vector3D vector3D::operator*(float t) const
{
	return vector3D(vecOrigin[0] * t, vecOrigin[1] * t, vecOrigin[2] * t);
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

	addOp.vecOrigin[0] = vecOrigin[0] + other[0];
	addOp.vecOrigin[1] = vecOrigin[1] + other[1];
	addOp.vecOrigin[2] = vecOrigin[2] + other[2];

	return addOp;
}

//Operator -
inline vector3D vector3D::operator-(vector3D other) const
{
	vector3D subOp(0, 0, 0);

	subOp.vecOrigin[0] = vecOrigin[0] - other[0];
	subOp.vecOrigin[1] = vecOrigin[1] - other[1];
	subOp.vecOrigin[2] = vecOrigin[2] - other[2];

	return subOp;
}

//Operator ==
inline bool vector3D::operator==(const vector3D &other)
{
	return vecOrigin[0] == other[0] && vecOrigin[1] == other[1] && vecOrigin[2] == other[2];
}

//Operator !=
inline bool vector3D::operator!=(const vector3D &other)
{
	return vecOrigin[0] != other[0] && vecOrigin[1] != other[1] && vecOrigin[2] != other[2];
}

//Operator =
inline vector3D vector3D::operator=(const vector3D &other)
{
	for (int i = 0; i < 4; ++i)
		vecOrigin[i] = other[i];
	return *this;
}

inline float& vector3D::operator[](int pos)
{
	return vecOrigin[pos];
}

inline const float& vector3D::operator[](int pos) const
{
	return vecOrigin[pos];
}

//Operator += for RayTrace
inline vector3D& vector3D::operator+=(const vector3D &v)
{
	vecOrigin[0] += v[0];
	vecOrigin[1] += v[1];
	vecOrigin[2] += v[2];

	return *this;
}

//Operator -= for RayTrace
inline vector3D& vector3D::operator-=(const vector3D &v)
{
	vecOrigin[0] -= v[0];
	vecOrigin[1] -= v[1];
	vecOrigin[2] -= v[2];

	return *this;
}

//Operator *= for RayTrace
inline vector3D& vector3D::operator*=(const vector3D &v)
{
	vecOrigin[0] *= v[0];
	vecOrigin[1] *= v[1];
	vecOrigin[2] *= v[2];

	return *this;
}

//Operator *= for RayTrace
inline vector3D& vector3D::operator*=(const float t)
{
	vecOrigin[0] *= t;
	vecOrigin[1] *= t;
	vecOrigin[2] *= t;

	return *this;
}

//Operator /= for RayTrace
inline vector3D& vector3D::operator/=(const vector3D &v)
{
	vecOrigin[0] /= v[0];
	vecOrigin[1] /= v[1];
	vecOrigin[2] /= v[2];

	return *this;
}

//Operator /= for RayTrace
inline vector3D& vector3D::operator/=(const float t)
{
	float k = 1.0/t;

	vecOrigin[0] *= k;
	vecOrigin[1] *= k;
	vecOrigin[2] *= k;

	return *this;
}

//Unit vector for RayTrace
inline vector3D unit_vector(vector3D v)
{
	return v / v.vecLength();
}

//Operator + for RayTrace
inline vector3D operator+(const vector3D &a, const vector3D &b)
{
	return vector3D(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

//Operator * for RayTrace
inline vector3D operator*(float t, const vector3D &other)
{
	return vector3D(t * other[0], t * other[1], t * other[2]);
}

//Negative value for vector for RayTrace
inline vector3D negativeVec(vector3D v)
{
	return vector3D(-v[0], -v[1], -v[2]);
}