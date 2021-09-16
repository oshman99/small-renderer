#ifndef HITTBLE_H
#define HITTBLE_H

#include <common_stuff.h>

class Material;

struct hit_record
{
    point3 p;
    vec3 normal;
    double t;
    std::shared_ptr<Material> mat_ptr;
    bool front_face;

    inline void set_face_and_normal(const ray& r, const vec3& outward_normal)
    {
        front_face = (dot(r.direction(), outward_normal) < 0);
        normal = front_face? outward_normal: -outward_normal;
    }
};

class Hittable
{
    public:
    //= 0 - pure virtual method, implementation should be provided by deriving class, const - not suppose to cahnge data of the class
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif