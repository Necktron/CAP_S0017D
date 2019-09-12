#ifndef RAYH
#define RAYH
#include "Vector3D.h"

class Ray
{
	public:
		Ray() {}
		Ray(const vector3D& a, const vector3D& b) { A = a; B = b; }
		vector3D origin() const { return A; }
		vector3D direction() const { return B; }
		vector3D pointAtParam(float t) const { return A + t*B; }

		vector3D A;
		vector3D B;
};

#endif