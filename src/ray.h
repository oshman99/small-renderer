#ifndef RAY_H
#define RAY_H
#include "vec3.h"
class ray {
    public:
        //constructors
        ray(){}
        ray(const point3 &origin, const vec3 &driection)
            : orig(origin), dir(driection) 
        {}
        
        point3 origin() const {return orig;}
        vec3 direction() const {return dir;}

        point3 at(double t) const{
            return orig + t*dir;
            
        }
    public:
    point3 orig;
    vec3 dir;
};
#endif