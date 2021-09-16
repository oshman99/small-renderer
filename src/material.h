#ifndef MATERIAL_H
#define MATERIAL_H
#include "common_stuff.h"
#include "hittable.h"
//struct hit_record;

class Material
{
    public:
    virtual bool scatter (
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
    
};

class Lambertian: public Material
{
    public:
        Lambertian(const color& mat_albedo):albedo(mat_albedo){}

        virtual bool scatter (
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
        {
            vec3 scatter_direction = rec.normal + random_unit_vector();
            if(scatter_direction.near_zero())
                scatter_direction = rec.normal;
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
    public:
        color albedo;
    
};

class Metal: public Material
{
    public:
        Metal(const color& mat_albedo):albedo(mat_albedo){}

        virtual bool scatter (
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
        {
            vec3 reflcted = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflcted);
            attenuation = albedo;
            return dot(scattered.direction(), rec.normal);
        }
    public:
        color albedo;
    
};

#endif