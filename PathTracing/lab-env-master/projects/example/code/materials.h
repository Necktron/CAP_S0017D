#ifndef MATERIALSH
#define MATERIALSH
#include "hitable.h"

class material
{
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec, vector3D& attenuation, Ray& scattered) const = 0;
};

#endif