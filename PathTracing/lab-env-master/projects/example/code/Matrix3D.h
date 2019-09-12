#pragma once
#include <iostream>
#include "Vector3D.h"
#include "math.h"
#include <cmath>

#define DEGREES_TO_RADIANS(degrees)((3.14159265359f * degrees)/180.0f)

using namespace std;

class matrix3D
{
public:
	//Basic constructors
	matrix3D();
	matrix3D(float, float, float, float, float, float, float, float, float);
	matrix3D(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

	//Identity constructor
	matrix3D(char flag);

	//Copy constructor
	matrix3D(const matrix3D &other);

	//Destructor
	~matrix3D();

	//Main matrix that you play around with
	float mxOrigin[4][4];

	struct Frustum
	{
		float near = 1;
		float far = 2;
		float left = 0;
		float right = 1;
		float top = 1;
		float bottom = 0;
		float fov = 90;
	};

	//Operators
	matrix3D operator*(const matrix3D other);
	vector3D operator*(const vector3D &other);
	matrix3D operator=(const matrix3D &other);
	matrix3D operator[](const matrix3D &other);

	//Functions		
	float getmxComp(int x, int y);
	void setmxComp(int x, int y, float value);
	vector3D vectorToMatrix(vector3D other);
	matrix3D transpose();
	matrix3D inverse();
	static matrix3D mxRotX(float angle);
	static matrix3D mxRotY(float angle);
	static matrix3D mxRotZ(float angle);
	static matrix3D scalematrix(float scale);
	matrix3D mxRotAroundVec(vector3D arbit, float angle);
	matrix3D translationMatrix(vector3D pos);
	void setPosition(vector3D);
	vector3D getPosition();
	static matrix3D ProjectionMatrix(float angleOfView, float near, float far, int width, int height);
	static matrix3D LookAt(vector3D eye, vector3D target, vector3D upDir);
};

//Empty constructor
inline matrix3D::matrix3D()
{
	mxOrigin[0][0] = 1;
	mxOrigin[0][1] = 0;
	mxOrigin[0][2] = 0;
	mxOrigin[0][3] = 0;

	mxOrigin[1][0] = 0;
	mxOrigin[1][1] = 1;
	mxOrigin[1][2] = 0;
	mxOrigin[1][3] = 0;

	mxOrigin[2][0] = 0;
	mxOrigin[2][1] = 0;
	mxOrigin[2][2] = 1;
	mxOrigin[2][3] = 0;

	mxOrigin[3][0] = 0;
	mxOrigin[3][1] = 0;
	mxOrigin[3][2] = 0;
	mxOrigin[3][3] = 1;
}

//Constructor with components
inline matrix3D::matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	mxOrigin[0][0] = a;
	mxOrigin[0][1] = b;
	mxOrigin[0][2] = c;
	mxOrigin[0][3] = 0;

	mxOrigin[1][0] = d;
	mxOrigin[1][1] = e;
	mxOrigin[1][2] = f;
	mxOrigin[1][3] = 0;

	mxOrigin[2][0] = g;
	mxOrigin[2][1] = h;
	mxOrigin[2][2] = i;
	mxOrigin[2][3] = 0;

	mxOrigin[3][0] = 0;
	mxOrigin[3][1] = 0;
	mxOrigin[3][2] = 0;
	mxOrigin[3][3] = 1;
}

//Constructor with components
inline matrix3D::matrix3D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	mxOrigin[0][0] = a;
	mxOrigin[0][1] = b;
	mxOrigin[0][2] = c;
	mxOrigin[0][3] = d;

	mxOrigin[1][0] = e;
	mxOrigin[1][1] = f;
	mxOrigin[1][2] = g;
	mxOrigin[1][3] = h;

	mxOrigin[2][0] = i;
	mxOrigin[2][1] = j;
	mxOrigin[2][2] = k;
	mxOrigin[2][3] = l;

	mxOrigin[3][0] = m;
	mxOrigin[3][1] = n;
	mxOrigin[3][2] = o;
	mxOrigin[3][3] = p;
}

//Index matrix constructor
inline matrix3D::matrix3D(char flag)
{
	if (flag == 'I')
	{
		mxOrigin[0][0] = 1;
		mxOrigin[0][1] = 0;
		mxOrigin[0][2] = 0;
		mxOrigin[0][3] = 0;

		mxOrigin[1][0] = 0;
		mxOrigin[1][1] = 1;
		mxOrigin[1][2] = 0;
		mxOrigin[1][3] = 0;

		mxOrigin[2][0] = 0;
		mxOrigin[2][1] = 0;
		mxOrigin[2][2] = 1;
		mxOrigin[2][3] = 0;

		mxOrigin[3][0] = 0;
		mxOrigin[3][1] = 0;
		mxOrigin[3][2] = 0;
		mxOrigin[3][3] = 1;
	}
}

//Copy Constructor
inline matrix3D::matrix3D(const matrix3D &other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			mxOrigin[i][j] = other.mxOrigin[i][j];
		}
}

//Destructor
inline matrix3D::~matrix3D()
{

}

//Get element
inline float matrix3D::getmxComp(int x, int y)
{
	if (x > 2 || y > 2)
	{
		cout << "Error! Index out of range, max value is 2" << endl;
		return 0;
	}
	else
	{
		return mxOrigin[x][y];
	}
}

//Set element
inline void matrix3D::setmxComp(int x, int y, float value)
{
	mxOrigin[x][y] = value;
}

//Transformation of 3D vector
inline vector3D matrix3D::vectorToMatrix(vector3D other)
{
	vector3D vecMx(0, 0, 0);

	vecMx.vecOrigin[0] = mxOrigin[0][0] * other.vecOrigin[0] + mxOrigin[0][1] * other.vecOrigin[1] + mxOrigin[0][2] * other.vecOrigin[2] + mxOrigin[0][3] * other.vecOrigin[3];
	vecMx.vecOrigin[1] = mxOrigin[1][0] * other.vecOrigin[0] + mxOrigin[1][1] * other.vecOrigin[1] + mxOrigin[1][2] * other.vecOrigin[2] + mxOrigin[1][3] * other.vecOrigin[3];
	vecMx.vecOrigin[2] = mxOrigin[2][0] * other.vecOrigin[0] + mxOrigin[2][1] * other.vecOrigin[1] + mxOrigin[2][2] * other.vecOrigin[2] + mxOrigin[2][3] * other.vecOrigin[3];
	vecMx.vecOrigin[3] = 1.0f;

	return vecMx;
}

//Transpose of 3D matrix, rows and colums switch places
inline matrix3D matrix3D::transpose()
{
	matrix3D mxTranspose;

	mxTranspose.mxOrigin[0][0] = mxOrigin[0][0];
	mxTranspose.mxOrigin[0][1] = mxOrigin[1][0];
	mxTranspose.mxOrigin[0][2] = mxOrigin[2][0];
	mxTranspose.mxOrigin[0][3] = mxOrigin[3][0];

	mxTranspose.mxOrigin[1][0] = mxOrigin[0][1];
	mxTranspose.mxOrigin[1][1] = mxOrigin[1][1];
	mxTranspose.mxOrigin[1][2] = mxOrigin[2][1];
	mxTranspose.mxOrigin[1][3] = mxOrigin[3][1];

	mxTranspose.mxOrigin[2][0] = mxOrigin[0][2];
	mxTranspose.mxOrigin[2][1] = mxOrigin[1][2];
	mxTranspose.mxOrigin[2][2] = mxOrigin[2][2];
	mxTranspose.mxOrigin[2][3] = mxOrigin[3][2];

	mxTranspose.mxOrigin[3][0] = mxOrigin[0][3];
	mxTranspose.mxOrigin[3][1] = mxOrigin[1][3];
	mxTranspose.mxOrigin[3][2] = mxOrigin[2][3];
	mxTranspose.mxOrigin[3][3] = mxOrigin[3][3];

	return mxTranspose;
}

//Inverse
inline matrix3D matrix3D::inverse()
{
	matrix3D mxInverse(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//All coordinates are set to A11 - A44, easier to debug with examples from internet; where all indexes are A[row][colum] and begins at 1 instead of 0
	float* A11 = &this->mxOrigin[0][0];
	float* A12 = &this->mxOrigin[0][1];
	float* A13 = &this->mxOrigin[0][2];
	float* A14 = &this->mxOrigin[0][3];

	float* A21 = &this->mxOrigin[1][0];
	float* A22 = &this->mxOrigin[1][1];
	float* A23 = &this->mxOrigin[1][2];
	float* A24 = &this->mxOrigin[1][3];

	float* A31 = &this->mxOrigin[2][0];
	float* A32 = &this->mxOrigin[2][1];
	float* A33 = &this->mxOrigin[2][2];
	float* A34 = &this->mxOrigin[2][3];

	float* A41 = &this->mxOrigin[3][0];
	float* A42 = &this->mxOrigin[3][1];
	float* A43 = &this->mxOrigin[3][2];
	float* A44 = &this->mxOrigin[3][3];

	//Calculates the determinant
	float detA = ((*A11 * *A22 * *A33 * *A44) + (*A11 * *A23 * *A34 * *A42) + (*A11 * *A24 * *A32 * *A42) + (*A12 * *A21 * *A34 * *A43) + (*A12 * *A23 * *A31 * *A44) + (*A12 * *A24 * *A33 * *A41) + (*A13 * *A21 * *A32 * *A44) + (*A13 * *A22 * *A34 * *A41) + (*A13 * *A24 * *A31 * *A42) + (*A14 * *A21 * *A33 * *A42) + (*A14 * *A22 * *A31 * *A43) + (*A14 * *A23 * *A32 * *A41) - (*A11 * *A22 * *A34 * *A43) - (*A11 * *A23 * *A32 * *A44) - (*A11 * *A24 * *A33 * *A42) - (*A12 * *A21 * *A33 * *A44) - (*A12 * *A23 * *A34 * *A41) - (*A12 * *A24 * *A31 * *A43) - (*A13 * *A21 * *A34 * *A42) - (*A13 * *A22 * *A31 * *A44) - (*A13 * *A24 * *A32 * *A41) - (*A14 * *A21 * *A32 * *A43) - (*A14 * *A22 * *A33 * *A41) - (*A14 * *A23 * *A31 * *A42));

	//If the determinant is 0, return the matrix without any modifications
	if (detA == 0)
	{
		cout << "The determinant is equal to zero, no inverse exsists!" << endl;
		return this->mxOrigin[4][4];
	}

	//If it's not 0, multiply 1 divided by the determinant into the matrix and return it
	else
	{
		cout << detA << endl;

		mxInverse.mxOrigin[0][0] = (1 / detA) * (*A22 * *A33 * *A44 + *A23 * *A34 * *A42 + *A24 * *A32 * *A43 - *A22 * *A34 * *A43 - *A23 * *A32 * *A44 - *A24 * *A33 * *A42);
		mxInverse.mxOrigin[0][1] = (1 / detA) * (*A12 * *A34 * *A43 + *A13 * *A32 * *A44 + *A14 * *A33 * *A42 - *A12 * *A33 * *A44 - *A13 * *A34 * *A42 - *A14 * *A32 * *A43);
		mxInverse.mxOrigin[0][2] = (1 / detA) * (*A12 * *A23 * *A44 + *A13 * *A24 * *A42 + *A14 * *A22 * *A43 - *A12 * *A24 * *A43 - *A13 * *A22 * *A44 - *A14 * *A23 * *A42);
		mxInverse.mxOrigin[0][3] = (1 / detA) * (*A12 * *A24 * *A33 + *A13 * *A22 * *A34 + *A14 * *A23 * *A32 - *A12 * *A23 * *A34 - *A13 * *A24 * *A32 - *A14 * *A22 * *A33);


		mxInverse.mxOrigin[1][0] = (1 / detA) * (*A21 * *A34 * *A43 + *A23 * *A31 * *A44 + *A24 * *A33 * *A41 - *A21 * *A33 * *A44 - *A23 * *A34 * *A41 - *A24 * *A31 * *A43);
		mxInverse.mxOrigin[1][1] = (1 / detA) * (*A11 * *A33 * *A44 + *A13 * *A34 * *A41 + *A14 * *A31 * *A43 - *A11 * *A34 * *A43 - *A13 * *A31 * *A44 - *A14 * *A33 * *A41);
		mxInverse.mxOrigin[1][2] = (1 / detA) * (*A11 * *A24 * *A43 + *A13 * *A21 * *A44 + *A14 * *A23 * *A41 - *A11 * *A23 * *A44 - *A13 * *A24 * *A41 - *A14 * *A21 * *A43);
		mxInverse.mxOrigin[1][3] = (1 / detA) * (*A11 * *A23 * *A34 + *A13 * *A24 * *A31 + *A14 * *A21 * *A33 - *A11 * *A24 * *A33 - *A13 * *A21 * *A34 - *A14 * *A23 * *A31);


		mxInverse.mxOrigin[2][0] = (1 / detA) * (*A21 * *A32 * *A44 + *A22 * *A34 * *A41 + *A24 * *A31 * *A42 - *A21 * *A34 * *A42 - *A22 * *A31 * *A44 - *A24 * *A32 * *A41);
		mxInverse.mxOrigin[2][1] = (1 / detA) * (*A11 * *A34 * *A42 + *A12 * *A31 * *A44 + *A14 * *A32 * *A41 - *A11 * *A32 * *A44 - *A12 * *A34 * *A41 - *A14 * *A31 * *A42);
		mxInverse.mxOrigin[2][2] = (1 / detA) * (*A11 * *A22 * *A44 + *A12 * *A24 * *A41 + *A14 * *A21 * *A42 - *A11 * *A24 * *A42 - *A12 * *A21 * *A44 - *A14 * *A22 * *A41);	
		mxInverse.mxOrigin[2][3] = (1 / detA) * (*A11 * *A24 * *A32 + *A12 * *A21 * *A34 + *A14 * *A22 * *A31 - *A11 * *A22 * *A34 - *A12 * *A24 * *A31 - *A14 * *A21 * *A32);


		mxInverse.mxOrigin[3][0] = (1 / detA) * (*A21 * *A33 * *A42 + *A22 * *A31 * *A43 + *A23 * *A32 * *A41 - *A21 * *A32 * *A43 - *A22 * *A33 * *A41 - *A23 * *A31 * *A42);
		mxInverse.mxOrigin[3][1] = (1 / detA) * (*A11 * *A32 * *A43 + *A12 * *A33 * *A41 + *A13 * *A31 * *A42 - *A11 * *A33 * *A42 - *A12 * *A31 * *A43 - *A13 * *A32 * *A41);
		mxInverse.mxOrigin[3][2] = (1 / detA) * (*A11 * *A23 * *A42 + *A12 * *A21 * *A43 + *A13 * *A22 * *A41 - *A11 * *A22 * *A43 - *A12 * *A23 * *A41 - *A13 * *A21 * *A42);	
		mxInverse.mxOrigin[3][3] = (1 / detA) * (*A11 * *A22 * *A33 + *A12 * *A23 * *A31 + *A13 * *A21 * *A32 - *A11 * *A23 * *A32 - *A12 * *A21 * *A33 - *A13 * *A22 * *A31);

		return mxInverse;
	}
}

//Rotation for matrix around X-axis
inline matrix3D matrix3D::mxRotX(float angle)
{
	matrix3D mxRotated(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Turns the degrees into radians
	float degToRad = 0.0f;
	degToRad = (angle * 3.14159265f / 180.0f);

	mxRotated.mxOrigin[0][0] = (1);
	mxRotated.mxOrigin[0][1] = (0);
	mxRotated.mxOrigin[0][2] = (0);
	mxRotated.mxOrigin[0][3] = (0);

	mxRotated.mxOrigin[1][0] = (0);
	mxRotated.mxOrigin[1][1] = (cos(degToRad));
	mxRotated.mxOrigin[1][2] = (-sin(degToRad));
	mxRotated.mxOrigin[1][3] = (0);

	mxRotated.mxOrigin[2][0] = (0);
	mxRotated.mxOrigin[2][1] = (sin(degToRad));
	mxRotated.mxOrigin[2][2] = (cos(degToRad));
	mxRotated.mxOrigin[2][3] = (0);

	mxRotated.mxOrigin[3][0] = (0);
	mxRotated.mxOrigin[3][1] = (0);
	mxRotated.mxOrigin[3][2] = (0);
	mxRotated.mxOrigin[3][3] = (1);

	return mxRotated;
}

//Rotation for matrix around Y-axis
inline matrix3D matrix3D::mxRotY(float angle)
{
	matrix3D mxRotated(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Turns the degrees into radians
	float degToRad = 0.0f;
	degToRad = (angle * 3.14159265f / 180.0f);

	mxRotated.mxOrigin[0][0] = (cos(degToRad));
	mxRotated.mxOrigin[0][1] = (0);
	mxRotated.mxOrigin[0][2] = (sin(degToRad));
	mxRotated.mxOrigin[0][3] = (0);

	mxRotated.mxOrigin[1][0] = (0);
	mxRotated.mxOrigin[1][1] = (1);
	mxRotated.mxOrigin[1][2] = (0);
	mxRotated.mxOrigin[1][3] = (0);

	mxRotated.mxOrigin[2][0] = (-sin(degToRad));
	mxRotated.mxOrigin[2][1] = (0);
	mxRotated.mxOrigin[2][2] = (cos(degToRad));
	mxRotated.mxOrigin[2][3] = (0);

	mxRotated.mxOrigin[3][0] = (0);
	mxRotated.mxOrigin[3][1] = (0);
	mxRotated.mxOrigin[3][2] = (0);
	mxRotated.mxOrigin[3][3] = (1);

	return mxRotated;
}

inline matrix3D matrix3D::scalematrix(float scale)
{
	matrix3D m;

	m.mxOrigin[0][0] = scale;
	m.mxOrigin[1][1] = scale;
	m.mxOrigin[2][2] = scale;

	return m;
}

//Rotation for matrix around Z-axis
inline matrix3D matrix3D::mxRotZ(float angle)
{
	matrix3D mxRotated(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//Turns the degrees into radians
	float degToRad = 0.0f;
	degToRad = (angle * 3.14159265f / 180.0f);

	mxRotated.mxOrigin[0][0] = (cos(degToRad));
	mxRotated.mxOrigin[0][1] = (-sin(degToRad));
	mxRotated.mxOrigin[0][2] = (0);
	mxRotated.mxOrigin[0][3] = (0);

	mxRotated.mxOrigin[1][0] = (sin(degToRad));
	mxRotated.mxOrigin[1][1] = (cos(degToRad));
	mxRotated.mxOrigin[1][2] = (0);
	mxRotated.mxOrigin[1][3] = (0);

	mxRotated.mxOrigin[2][0] = (0);
	mxRotated.mxOrigin[2][1] = (0);
	mxRotated.mxOrigin[2][2] = (1);
	mxRotated.mxOrigin[2][3] = (0);

	mxRotated.mxOrigin[3][0] = (0);
	mxRotated.mxOrigin[3][1] = (0);
	mxRotated.mxOrigin[3][2] = (0);
	mxRotated.mxOrigin[3][3] = (1);

	return mxRotated;
}

//Rotation for matrix around arbitrary vector
inline matrix3D matrix3D::mxRotAroundVec(vector3D arbit, float angle)
{
	matrix3D arbitRot(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	float u = arbit.vecGet(0);
	float v = arbit.vecGet(1);
	float w = arbit.vecGet(2);

	float L = (u*u + v * v + w * w);

	//Turns the degrees into radians
	float degToRad = (angle * 3.14159265f / 180.0f);

	float u2 = u * u;
	float v2 = v * v;
	float w2 = w * w;

	arbitRot.mxOrigin[0][0] = (u2 + (v2 + w2) * cos(degToRad)) / L;
	arbitRot.mxOrigin[0][1] = (u * v * (1 - cos(degToRad)) - w * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[0][2] = (u * w * (1 - cos(degToRad)) + v * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[0][3] = 0.0;

	arbitRot.mxOrigin[1][0] = (u * v * (1 - cos(degToRad)) + w * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[1][1] = (v2 + (u2 + w2) * cos(degToRad)) / L;
	arbitRot.mxOrigin[1][2] = (v * w * (1 - cos(degToRad)) - u * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[1][3] = 0.0;

	arbitRot.mxOrigin[2][0] = (u * w * (1 - cos(degToRad)) - v * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[2][1] = (v * w * (1 - cos(degToRad)) + u * sqrt(L) * sin(degToRad)) / L;
	arbitRot.mxOrigin[2][2] = (w2 + (u2 + v2) * cos(degToRad)) / L;
	arbitRot.mxOrigin[2][3] = 0.0;

	arbitRot.mxOrigin[3][0] = 0.0;
	arbitRot.mxOrigin[3][1] = 0.0;
	arbitRot.mxOrigin[3][2] = 0.0;
	arbitRot.mxOrigin[3][3] = 1.0;

	return arbitRot;
}

//Operator *, vector and matrix
inline vector3D matrix3D::operator*(const vector3D &other)
{
	vector3D ockelbo;

	ockelbo.vecOrigin[0] = (this->mxOrigin[0][0] * other.vecOrigin[0]) + (this->mxOrigin[0][1] * other.vecOrigin[1]) + (this->mxOrigin[0][2] * other.vecOrigin[2]) + (this->mxOrigin[0][3] * other.vecOrigin[3]);
	ockelbo.vecOrigin[1] = (this->mxOrigin[1][0] * other.vecOrigin[0]) + (this->mxOrigin[1][1] * other.vecOrigin[1]) + (this->mxOrigin[1][2] * other.vecOrigin[2]) + (this->mxOrigin[1][3] * other.vecOrigin[3]);
	ockelbo.vecOrigin[2] = (this->mxOrigin[2][0] * other.vecOrigin[0]) + (this->mxOrigin[2][1] * other.vecOrigin[1]) + (this->mxOrigin[2][2] * other.vecOrigin[2]) + (this->mxOrigin[2][3] * other.vecOrigin[3]);
	ockelbo.vecOrigin[3] = 1.0f;

	return ockelbo;
}

//Operator *, matrix and matrix
inline matrix3D matrix3D::operator*(matrix3D other)
{
	matrix3D mxMult;

	mxMult.mxOrigin[0][0] = mxOrigin[0][0] * other.mxOrigin[0][0] + mxOrigin[0][1] * other.mxOrigin[1][0] + mxOrigin[0][2] * other.mxOrigin[2][0] + mxOrigin[0][3] * other.mxOrigin[3][0];
	mxMult.mxOrigin[0][1] = mxOrigin[0][0] * other.mxOrigin[0][1] + mxOrigin[0][1] * other.mxOrigin[1][1] + mxOrigin[0][2] * other.mxOrigin[2][1] + mxOrigin[0][3] * other.mxOrigin[3][1];
	mxMult.mxOrigin[0][2] = mxOrigin[0][0] * other.mxOrigin[0][2] + mxOrigin[0][1] * other.mxOrigin[1][2] + mxOrigin[0][2] * other.mxOrigin[2][2] + mxOrigin[0][3] * other.mxOrigin[3][2];
	mxMult.mxOrigin[0][3] = mxOrigin[0][0] * other.mxOrigin[0][3] + mxOrigin[0][1] * other.mxOrigin[1][3] + mxOrigin[0][2] * other.mxOrigin[2][3] + mxOrigin[0][3] * other.mxOrigin[3][3];

	mxMult.mxOrigin[1][0] = mxOrigin[1][0] * other.mxOrigin[0][0] + mxOrigin[1][1] * other.mxOrigin[1][0] + mxOrigin[1][2] * other.mxOrigin[2][0] + mxOrigin[1][3] * other.mxOrigin[3][0];
	mxMult.mxOrigin[1][1] = mxOrigin[1][0] * other.mxOrigin[0][1] + mxOrigin[1][1] * other.mxOrigin[1][1] + mxOrigin[1][2] * other.mxOrigin[2][1] + mxOrigin[1][3] * other.mxOrigin[3][1];
	mxMult.mxOrigin[1][2] = mxOrigin[1][0] * other.mxOrigin[0][2] + mxOrigin[1][1] * other.mxOrigin[1][2] + mxOrigin[1][2] * other.mxOrigin[2][2] + mxOrigin[1][3] * other.mxOrigin[3][2];
	mxMult.mxOrigin[1][3] = mxOrigin[1][0] * other.mxOrigin[0][3] + mxOrigin[1][1] * other.mxOrigin[1][3] + mxOrigin[1][2] * other.mxOrigin[2][3] + mxOrigin[1][3] * other.mxOrigin[3][3];

	mxMult.mxOrigin[2][0] = mxOrigin[2][0] * other.mxOrigin[0][0] + mxOrigin[2][1] * other.mxOrigin[1][0] + mxOrigin[2][2] * other.mxOrigin[2][0] + mxOrigin[2][3] * other.mxOrigin[3][0];
	mxMult.mxOrigin[2][1] = mxOrigin[2][0] * other.mxOrigin[0][1] + mxOrigin[2][1] * other.mxOrigin[1][1] + mxOrigin[2][2] * other.mxOrigin[2][1] + mxOrigin[2][3] * other.mxOrigin[3][1];
	mxMult.mxOrigin[2][2] = mxOrigin[2][0] * other.mxOrigin[0][2] + mxOrigin[2][1] * other.mxOrigin[1][2] + mxOrigin[2][2] * other.mxOrigin[2][2] + mxOrigin[2][3] * other.mxOrigin[3][2];
	mxMult.mxOrigin[2][3] = mxOrigin[2][0] * other.mxOrigin[0][3] + mxOrigin[2][1] * other.mxOrigin[1][3] + mxOrigin[2][2] * other.mxOrigin[2][3] + mxOrigin[2][3] * other.mxOrigin[3][3];

	mxMult.mxOrigin[3][0] = mxOrigin[3][0] * other.mxOrigin[0][0] + mxOrigin[3][1] * other.mxOrigin[1][0] + mxOrigin[3][2] * other.mxOrigin[2][0] + mxOrigin[3][3] * other.mxOrigin[3][0];
	mxMult.mxOrigin[3][1] = mxOrigin[3][0] * other.mxOrigin[0][1] + mxOrigin[3][1] * other.mxOrigin[1][1] + mxOrigin[3][2] * other.mxOrigin[2][1] + mxOrigin[3][3] * other.mxOrigin[3][1];
	mxMult.mxOrigin[3][2] = mxOrigin[3][0] * other.mxOrigin[0][2] + mxOrigin[3][1] * other.mxOrigin[1][2] + mxOrigin[3][2] * other.mxOrigin[2][2] + mxOrigin[3][3] * other.mxOrigin[3][2];
	mxMult.mxOrigin[3][3] = 1.0f;

	return mxMult;
}

//Operator =
inline matrix3D matrix3D::operator=(const matrix3D &other)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			mxOrigin[i][j] = other.mxOrigin[i][j];
		}
	return *this;
}

//Operator ()
inline matrix3D matrix3D::operator[](const matrix3D &other)
{
	return mxOrigin[0][0];
}

//Translation Matrix
inline matrix3D matrix3D::translationMatrix(vector3D pos)
{
	matrix3D translation;

	translation.mxOrigin[0][0] = 1;
	translation.mxOrigin[0][1] = 0;
	translation.mxOrigin[0][2] = 0;
	translation.mxOrigin[0][3] = pos.vecGet(0);

	translation.mxOrigin[1][0] = 0;
	translation.mxOrigin[1][1] = 1;
	translation.mxOrigin[1][2] = 0;
	translation.mxOrigin[1][3] = pos.vecGet(1);

	translation.mxOrigin[2][0] = 0;
	translation.mxOrigin[2][1] = 0;
	translation.mxOrigin[2][2] = 1;
	translation.mxOrigin[2][3] = pos.vecGet(2);

	translation.mxOrigin[3][0] = 0;
	translation.mxOrigin[3][1] = 0;
	translation.mxOrigin[3][2] = 0;
	translation.mxOrigin[3][3] = 1;

	return translation;
}

//Set position
inline void matrix3D::setPosition(vector3D pos)
{
	mxOrigin[3][0] = pos.vecGet(0);
	mxOrigin[3][1] = pos.vecGet(1);
	mxOrigin[3][2] = pos.vecGet(2);
}

//Get position
inline vector3D matrix3D::getPosition()
{
	return vector3D(mxOrigin[2][0], mxOrigin[2][1], mxOrigin[2][2]);
}

inline matrix3D matrix3D::ProjectionMatrix(float angleOfView, float zNear, float zFar, int width, int height)
{
	matrix3D m;
	const float ar = width / height;
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(DEGREES_TO_RADIANS(angleOfView / 2.0));

	Frustum frustum;

	frustum.near = zNear;
	frustum.far = zFar;
	frustum.fov = angleOfView;
	frustum.top = tan(angleOfView * 0.5 * 3.14f * 0.00555555f) * zNear;
	frustum.bottom = -frustum.top;
	frustum.right = frustum.top * 1;
	frustum.left = frustum.bottom * 1;

	float invWidth = 1 / (frustum.right - frustum.left);
	float invHeight = 1 / (frustum.top - frustum.bottom);
	float invLength = 1 / (zFar - zNear);

	m.mxOrigin[0][0] = 2 * zNear * invWidth;
	m.mxOrigin[0][2] = (frustum.right + frustum.left) * invWidth;
	m.mxOrigin[1][1] = 2 * zNear * invHeight;
	m.mxOrigin[1][2] = (frustum.top + frustum.bottom) * invHeight;
	m.mxOrigin[2][2] = -(zFar + zNear) * invLength;
	m.mxOrigin[2][3] = -2 * zFar * zNear * invLength;
	m.mxOrigin[3][2] = -1.0f;
	m.mxOrigin[3][3] = 0.0f;

	//NACKEN
	/*m.mxOrigin[0][0] = 1.0f;
	m.mxOrigin[0][1] = 0.0f;
	m.mxOrigin[0][2] = 0.0f;
	m.mxOrigin[0][3] = 0.0f;

	m.mxOrigin[1][0] = 0.0f;
	m.mxOrigin[1][1] = 1.0f;
	m.mxOrigin[1][2] = 0.0f;
	m.mxOrigin[1][3] = 0.0f;

	m.mxOrigin[2][0] = 0.0f;
	m.mxOrigin[2][1] = 0.0f;
	m.mxOrigin[2][2] = (zNear + zFar) / zRange;
	m.mxOrigin[2][3] = -1.0f;

	m.mxOrigin[3][0] = 0.0f;
	m.mxOrigin[3][1] = 0.0f;
	m.mxOrigin[3][2] = 2.0f * zFar * zNear / zRange;
	m.mxOrigin[3][3] = 0.0f;*/

	return m;
}

inline matrix3D matrix3D::LookAt(vector3D eye, vector3D target, vector3D upDir)
{
	vector3D zaxis = (eye - target).vecNormilisation();
	vector3D xaxis = (upDir.crossProd(zaxis)).vecNormilisation();
	vector3D yaxis = zaxis.crossProd(xaxis);

	matrix3D matrix(xaxis[0], yaxis[0], zaxis[0], 0.0f,
			xaxis[1], yaxis[1], zaxis[1], 0.0f,
			xaxis[2], yaxis[2], zaxis[2], 0.0f,
		-xaxis.dotProd(eye), -yaxis.dotProd(eye), -zaxis.dotProd(eye), 1.0f);

	return matrix;
}