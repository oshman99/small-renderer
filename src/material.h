#ifndef MATERIAL_H
#define MATERIAL_H
#include "common_stuff.h"

struct hit_record;

class Material
{
    public:
    virtual bool scatter (
        const ray& r_in, const hit_record& rec, const color& attenuation, ray& scattered) const = 0;
    
};

class Lambertian: public Material
{
    public:
        Lambertian(const color& mat_albedo):albedo(mat_albedo){}
        virtual bool scatter (
            const ray& r_in, const hit_record& rec, const color& attenuation, ray& scattered) const override
        {
            auto scatter_direction = rec.normal + random_unit_vector();
        }
    private:
        color albedo;
    
};

#endif