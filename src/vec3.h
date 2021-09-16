/*3d vector class*/
#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

class vec3
{
    //methods
    public:
        vec3(): e{0, 0, 0} {}
        vec3(double e1, double e2, double e3):e{e1, e2, e3} {}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}

        vec3 operator+=(const vec3 v) {
            e[0] += v[0];
            e[1] += v[1];
            e[2] += v[2];
            return *this;
        }

        vec3 operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3 operator/=(const double t) {
            
            return *this *= 1/t;
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const{
            return std::sqrt(length_squared());
        }

        inline static vec3 random()
        {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max)
        {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

        bool near_zero() const
        {
            const auto s = 1e-8;
            return(fabs(e[0] < s) && fabs(e[1] < s) && fabs(e[2] < s));
        }


    //data members
    public:
        double e[3];
};
// Type aliases for vec3
//Эти типы заменяются на vec3
using point3 = vec3;//3D point
using color = vec3;//RGB color

/*vec3 Utility functions
operator<<
operator+
operator-
operator* : with vec3
operator* : with scalar and vec3
operator* : with vec3 and scalar
operator/
double dot : dot product
vec3 cross : cross product
vec3 unit_vector : get unit vector(length = 1.0)
*/

inline std::ostream&  operator<<(std::ostream &out, const vec3 &v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2] );
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2] );
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2] );
}

inline vec3 operator*(const double s, const vec3 &v){
    return vec3(v.e[0] * s, v.e[1] * s, v.e[2] * s );
}

inline vec3 operator*(const vec3 &v,const double s){
    return s*v; 
}

inline vec3 operator/(const vec3 &v,const double s){
    return (1/s)*v; 
}

inline double dot(const vec3 &v1,const vec3 &v2){
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]; 
}

inline vec3 cross(const vec3 &v1,const vec3 &v2){
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1], 
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]); 
}

inline vec3 unit_vector(const vec3 &v){
    return v/v.length(); 
}


vec3 random_in_unit_sphere()
{
    while(true)
    {
        vec3 p = vec3::random(-1, 1);
        //length_squared() insted of length() to avoid useless calculations - 1^2 = 1 duh 
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal)
{
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return -in_unit_sphere; 
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2*dot(v,n)*n;//v - sended ray, n - normal, dot(v,n)*n - projection of v onto n, minus - projection is reversed, 2* - projection is now pointing to the top of reflected vector.
                            // better check scheme of vector mirror reflection
}

#endif