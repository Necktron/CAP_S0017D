//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "../../../engine/config.h"
#include "exampleapp.h"
#include "Vector3D.h"
#include "sphere.h"
#include "hitableList.h"
#include "float.h"
#include "camera.h"
#include "materials.h"

unsigned int width;
unsigned int height;
unsigned int RPP;
int sphereNum;
string saveIn;
string picName;
bool savePic = false;

int rayCount = 0;
int workTodo = 0;

//DIFFUSE SPHERE EDITION
vector3D random_in_unit_sphere()
{
	vector3D p;
	do {
		p = 2.0 * vector3D(drand48(), drand48(), drand48()) - vector3D(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

//DIFFUSE SPHERE EDITION
vector3D color(const Ray &r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, MAXFLOAT, rec))
	{
		Ray scattered;
		vector3D attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth+1);
		}

		else
		{
			return vector3D(0, 0, 0);
		}
	}

	else
	{
		vector3D unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction[1] + 1.0);
		return (1.0 - t) * vector3D(1.0, 1.0, 1.0) + t * vector3D(0.5, 0.7, 1.0);	
	}
}

//REFELCT
vector3D reflect(const vector3D& v, const vector3D& n)
{
	return v - 2 * dotProd(v, n) * n;
}

//REFRACT
bool refract(const vector3D& v, const vector3D& n, float ni_over_nt, vector3D& refracted)
{
	vector3D uv = unit_vector(v);
	float dt = dotProd(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}

	else return false;
}

//SCHLICK
float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

//LAMBERTIAN SPHERE EDITION
class lambertian : public material
{
    public:
        lambertian(const vector3D& a) : albedo(a) {}
        virtual bool scatter(const Ray& r_in, const hit_record& rec, vector3D& attenuation, Ray& scattered) const
        {
            vector3D target = rec.p + rec.normal + random_in_unit_sphere();
			scattered = Ray(rec.p, target - rec.p);
			attenuation = albedo;
			return true;
        }

		vector3D albedo;
};

//METAL SPHERE EDITION
class metal : public material
{
    public:
        metal(const vector3D& a, float f) : albedo(a) { if(f < 1) fuzz = f; else fuzz = 1; }
        virtual bool scatter(const Ray& r_in, const hit_record& rec, vector3D& attenuation, Ray& scattered) const
        {
			vector3D reflected = reflect(unit_vector(r_in.direction()), rec.normal);
			scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
			attenuation = albedo;
			return (dotProd(scattered.direction(), rec.normal) > 0);
        }

		vector3D albedo;
		float fuzz;
};

//DIELECTRIC SPHERE EDITION
class dielectric : public material
{
    public:
        dielectric(float ri) : ref_idx(ri) {}
        virtual bool scatter(const Ray& r_in, const hit_record& rec, vector3D& attenuation, Ray& scattered) const
        {
            vector3D outward_normal;
			vector3D reflected = reflect(r_in.direction(), rec.normal);
			float ni_over_nt;
			attenuation = vector3D(1.0, 1.0, 1.0);
			vector3D refracted;
			float reflect_prob;
			float cosine;
			if(dotProd(r_in.direction(), rec.normal) > 0)
			{
				outward_normal = negativeVec(rec.normal);
				ni_over_nt = ref_idx;
				cosine = ref_idx * dotProd(r_in.direction(), rec.normal) / r_in.direction().vecLength();
			}

			else
			{
				outward_normal = rec.normal;
				ni_over_nt = 1.0 / ref_idx;
				cosine = -dotProd(r_in.direction(), rec.normal) / r_in.direction().vecLength();
			}

			if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
			{
				reflect_prob = schlick(cosine, ref_idx);
			}

			else
			{
				reflect_prob = 1.0;
			}

			if (drand48() < reflect_prob)
			{
				scattered = Ray(rec.p, reflected);
			}

			else { scattered = Ray(rec.p, refracted); }

			return true;
        }

		float ref_idx;
};

//Pseudo Random Number Generator
int PRNG()
{
	srand(2141);
	int result = rand()%10;
	return result;
}

bool limitReached(int limit, int spheresAlive)
{
	if(spheresAlive >= limit)
	{
		return true;
	}

	else
	{
		return false;
	}
	
}

//HITABLE LAST CHAPTER
hitable *random_scene(int sphereBirth)
{
	int n = sphereBirth;
	hitable **list = new hitable*[n+1];
	list[0] = new sphere(vector3D(0, -1000, 0), 1000, new lambertian(vector3D(0.5, 0.5, 0.5)));
	int i = 1;
	for(int a = -11 ; a < 11 ; a++)
	{
		for(int b = -11 ; b < 11 ; b++)
		{
			float choose_mat = drand48();
			vector3D center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
			if((center - vector3D(4, 0.2, 0)).vecLength() > 0.9)
			{
				//DIFFUSE MAT
				if(choose_mat < 0.8)
				{
					list[i++] = new sphere(center, 0.2, new lambertian(vector3D(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));

					if(limitReached(n, i))
					{
						continue;
					}
				}

				//METAL MAT
				else if(choose_mat < 0.95)
				{
					list[i++] = new sphere(center, 0.2, new metal(vector3D(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));

					if(limitReached(n, i))
					{
						continue;
					}
				}

				//GLASS
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));

					if(limitReached(n, i))
					{
						continue;
					}
				}
			}
		}
	}

	list[i++] = new sphere(vector3D(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vector3D(-4, 1, 0), 1.0, new lambertian(vector3D(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vector3D(4, 1, 0), 1.0, new metal(vector3D(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}

//MAIN
int main(int argc, char const *argv[])
{
	/*
	TODO:
	1) Fix image name error
	2) Spheres don't spawn in written number, find other way to randomize a and b variables
	3) Fix calculation of progress through .exe runtime
	*/

	if(argc = 1 && argv[1] == "help")
	{
		wcout << "Example of input: int width, int height, int rays, int spheresToRender, true, MyPictureName" << endl;
	}

	else
	{
		if(argc > 5)
		{
			width = strtol(argv[1], NULL, 10);
			height = strtol(argv[2], NULL, 10);
			RPP = strtol(argv[3], NULL, 10);
			sphereNum = atoi(argv[4]);
			saveIn = argv[5];
			picName = argv[6];

			wcout << "Width: " << width << endl;
			wcout << "Height: " << height << endl;
			wcout << "Rays: " << RPP << endl;
			wcout << "Spheres: " << sphereNum << endl;
			cout << saveIn << endl;
			cout << picName << endl;
			wcout << "" << endl;
		}

		else
		{
			width = strtol(argv[1], NULL, 10);
			height = strtol(argv[2], NULL, 10);
			RPP = strtol(argv[3], NULL, 10);
			sphereNum = atoi(argv[4]);
			saveIn = argv[5];

			wcout << "Width: " << width << endl;
			wcout << "Height: " << height << endl;
			wcout << "Rays: " << RPP << endl;
			wcout << "Spheres: " << sphereNum << endl;
			wcout << "" << endl;
		}
		
		if(saveIn == "true")
		{
			savePic = true;
		}
	}

	if(savePic == true)
	{
		std::ofstream img(picName+ ".ppm");
		int nx = width;
		int ny = height;
		int ns = RPP;
		img << "P3\n" << nx << " " << ny << "\n255\n";

		hitable *world = random_scene(sphereNum);
		vector3D lookFrom(0, 2, 1);
		vector3D lookAt(0, 0, -1);
		float dist_to_focus = (lookFrom - lookAt).vecLength();
		float aperture = 2.0;

		camera cam(lookFrom, lookAt, vector3D(0, 1, 0), 90, float(nx)/float(ny), aperture, dist_to_focus);

		auto start = std::chrono::high_resolution_clock::now();

		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vector3D col(0, 0, 0);

				for (int s = 0; s < ns; s++)
				{
					float u = float(i + drand48()) / float(nx);
					float v = float(j + drand48()) / float(ny);
					Ray r = cam.get_ray(u, v);
					vector3D p = r.pointAtParam(2.0);
					col += color(r, world, 0);
				}

				col /= float(ns);
				col = vector3D(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
				int ir = int(255.99 * col[0]);
				int ig = int(255.99 * col[1]);
				int ib = int(255.99 * col[2]);
				img << ir << " " << ig << " " << ib << "\n";
			}
		}

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> exeTime = finish - start;

		wcout << "Progress Of Completion: 100%\n" << endl;

		int numberRes = PRNG();
		wcout << "Program reached the end! Random number from start was " << numberRes << endl;
		wcout << "Execution time: " << exeTime.count() << " sec" << endl;
		wcout << "Created Rays: " << rayCount << endl;
		wcout << "MRays/s: " << rayCount / exeTime.count() << endl;
		wcout << "* * * * * * * * * *" << endl;
	}

	else
	{
		int nx = width;
		int ny = height;
		int ns = RPP;
		workTodo = nx * ny * ns;

		hitable *world = random_scene(sphereNum);
		vector3D lookFrom(0, 2, 1);
		vector3D lookAt(0, 0, -1);
		float dist_to_focus = (lookFrom - lookAt).vecLength();
		float aperture = 2.0;

		camera cam(lookFrom, lookAt, vector3D(0, 1, 0), 90, float(nx)/float(ny), aperture, dist_to_focus);

		auto start = std::chrono::high_resolution_clock::now();

		for (int j = ny - 1; j >= 0; j--)
		{
			wcout << "Progress Of Completion: " << /*formula for calculating % of completion <<*/ "%\r";
			wcout.flush();

			for (int i = 0; i < nx; i++)
			{
				vector3D col(0, 0, 0);

				for (int s = 0; s < ns; s++)
				{
					float u = float(i + drand48()) / float(nx);
					float v = float(j + drand48()) / float(ny);
					Ray r = cam.get_ray(u, v);
					rayCount++;
					vector3D p = r.pointAtParam(2.0);
					col += color(r, world, 0);
				}
			}
		}

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> exeTime = finish - start;

		wcout << "Progress Of Completion: 100%\n" << endl;

		int numberRes = PRNG();
		wcout << "Program reached the end!" << endl;
		wcout << "Execution time: " << exeTime.count() << " sec" << endl;
		wcout << "Created Rays: " << rayCount << endl;
		wcout << "MRays/s: " << rayCount / exeTime.count() << endl;
		wcout << "* * * * * * * * * *" << endl;
	}
}