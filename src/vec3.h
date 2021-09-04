#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3
{
    //methods
    public:
        vec3(): elem{0, 0, 0} {}
        vec3(double elem1, double elem2, double elem3):elem{elem1, elem2, elem3} {}

        double x() const {return elem[0];}
        double y() const {return elem[1];}
        double z() const {return elem[2];}

        vec3 operator-() const {return vec3(-elem[0], -elem[1], -elem[2]);}
        double operator[](int i) const {return elem[i];}
        double& operator[](int i) {return elem[i];}
        vec3 operator+=(const vec3 v) {
            elem[0] += v[0];
            elem[1] += v[1];
            elem[2] += v[2];
            return *this;
        }
        vec3 operator*=(const double t) {
            elem[0] *= t;
            elem[1] *= t;
            elem[2] *= t;
            return *this;
        }
        vec3 operator/=(const double t) {
            
            return *this *= 1/t;
        }
        double length_squared() const {
            return elem[0]*elem[0] + elem[1]*elem[1] + elem[2]*elem[2];
        }
        double length() const{
            return std::sqrt(length_squared());
        }
    //data members
    public:
        double elem[3];
};
// Type aliases for vec3
//Эти типы заменяются на vec3
using point3 = vec3;//3D point
using color = vec3;//RGB color

//vec3 Utility functions
#endif