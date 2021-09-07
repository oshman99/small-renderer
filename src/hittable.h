#ifndef HITTBLE_H
#define HITTBLE_H

#include <ray.h>

struct hit_record
{
    point3 p;
    vec3 normal;
    double t;
};

class Hittable
{
    public:
    //= 0 - pure virtual method, implementation should be provided, const - not suppose to cahnge data of the class
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif