#ifndef COMMON_H
#define COMMON_H

//includes
#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility funcs
double degrees_to_radians (double degrees)
{
    return degrees * pi/180.0;
}

inline double random_double()
{
    return rand()/(RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

inline double clamp (double x, double min, double max)
{
    const double t = x < min? min : x;
    return t > max? max: t;
}



//Common headers
#include "ray.h"
#include "vec3.h"

#endif