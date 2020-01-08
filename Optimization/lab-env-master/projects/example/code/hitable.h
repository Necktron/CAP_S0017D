#ifndef HITABLEH
#define HITABLEH
#include "ray.h"

class material;

struct hit_record
{
    float t;
    vector3D p;
    vector3D normal;
    material *mat_ptr;
};

class hitable
{
    public:
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif