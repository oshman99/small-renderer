#ifndef SPHERE_H
#define SPHERE_H
#include <hittable.h>
#include <vec3.h>
class Sphere : public Hittable
{
    public:
        Sphere () {}
        Sphere(point3 cent, double r): center(cent), radius(r) {}
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
};

bool Sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    vec3 oc = r.origin() - center;
    //square equasin with a = dot(direction, direction) and b=2h
    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discr = half_b*half_b - a*c;

    if(discr < 0)
        return false;
    auto sqrtd = sqrt(discr);
    auto root = (-half_b - sqrtd) / a;
    //find nearest root in accceptable range
    if(root < t_min || t_max < root)
    {
        root = (-half_b + sqrtd) / a;
        if(root < t_min || t_max < root)
            return false;
    }
    rec.t  = root;
    rec.p = r.at(rec.t);
    //basicly unit vector computation,maybe just use unit_vector()?
    vec3 outward_normal = (rec.p - center)/radius;
    rec.set_face_and_normal(r, outward_normal);
    
    return true;
}
#endif