#ifndef CAMERAH
#define CAMERAH
#include "ray.h"

vector3D random_in_unit_disk()
{
    vector3D p;
    do{
        p = 2.0 * vector3D(drand48(), drand48(), 0) - vector3D(1, 1, 0);
    } while(dotProd(p, p) >= 1.0);
    return p;
}

class camera
{
    public:
        camera(vector3D lookFrom, vector3D lookAt, vector3D vup, float vfov, float aspect, float aperture, float focus_dist) {
            lens_radius = aperture / 2;
            float theta = vfov * M_PI / 180;
            float half_height = tan(theta / 2);
            float half_width = aspect * half_height;
            origin = lookFrom;
            w = unit_vector(lookFrom - lookAt);
            u = unit_vector(crossProd(vup, w));
            v = crossProd(w, u);
            lower_left_corner = origin - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }

        Ray get_ray(float s, float t)
        {
            vector3D rd = lens_radius * random_in_unit_disk();
            vector3D offset = u * rd[0] + v * rd[1]; 
            return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
        }

        vector3D origin;
        vector3D lower_left_corner;
        vector3D horizontal;
        vector3D vertical;
        vector3D u, v, w;
        float lens_radius;
};

#endif