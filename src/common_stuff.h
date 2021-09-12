#ifndef COMMON_H
#define COMMON_H

//includes
#include <cmath>
#include <limits>
#include <memory>

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility funcs
double degrees_to_radians (double degrees)
{
    return degrees * pi/180.0;
}

//Common headers
#include "ray.h"
#include "vec3.h"

#endif