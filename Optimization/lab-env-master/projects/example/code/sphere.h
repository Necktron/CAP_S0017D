#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"

class sphere: public hitable
{
    public:
        sphere() {}
        sphere(vector3D cen, float r, material* mat) : center(cen), radius(r), mat(mat) {};
        virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
        vector3D center;
        float radius;
        material* mat;
};

bool sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
{
    vector3D oc = r.origin() - center;
	float a = dotProd(r.direction(), r.direction());
	float b = dotProd(oc, r.direction());
	float c = dotProd(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.pointAtParam(rec.t);
            rec.normal = (rec.p - center) / radius;

            rec.mat_ptr = this->mat;

            return true;
        }

        temp = (-b + sqrtf(b * b - a * c)) / a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.pointAtParam(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = this->mat;
            return true;
        }
	}

    return false;
};

#endif