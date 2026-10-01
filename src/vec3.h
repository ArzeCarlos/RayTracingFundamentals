#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>


/** 
 * @brief: Represent a mathematical 3D vector
 *
 * @details The vec3 class represent a 3D vector.
 * It also provides basice vector operations, such as: addition,
 * multiplication, dot product, cross product, normalization.
 */

class vec3{
    public:
        double e[3];
        vec3() : e{0,0,0}{}
        vec3(double e0, double e1, double e2): e{e0,e1,e2}{}
        double x() const { return e[0];}
        double y() const { return e[1];}
        double z() const { return e[2];}
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }
        vec3& operator+=(const vec3& v) {
        e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
        return *this;}
        vec3& operator*=(double t) { e[0]*=t; e[1]*=t; e[2]*=t; return *this; }
        vec3& operator/=(double t) { return *this *= 1/t; }

        double length() const { return std::sqrt(length_squared()); }
        double length_squared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
        bool near_zero() const {
            // Return true if the vector is close to zero in all dimensions.
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline vec3 operator+(const vec3&u, const vec3&v){
    return vec3(u[0]+v[0], u[1]+v[1], u[2]+v[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u[0]-v[0], u[1]-v[1], u[2]-v[2]);
}
inline vec3 operator*(double t, const vec3&u){
    return vec3(t*u[0],t*u[1],t*u[2]);
} 
inline vec3 operator*(const vec3& v, double t) { 
    return t * v; 
}
inline double dot(const vec3&u, const vec3&v){
    return u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
}
inline vec3 cross(const vec3&u, const vec3&v){
    double i_comp=u[1]*v[2]-u[2]*v[1];
    double j_comp=u[2]*v[0]-u[0]*v[2];
    double k_comp=u[0]*v[1]-u[1]*v[0];
    return vec3(i_comp,j_comp,k_comp);
}
inline double length(const vec3& v) {
    return std::sqrt(dot(v, v));
}


inline vec3 operator/(const vec3& v, double t) {
    return (1.0 / t) * v;
}

inline vec3 unit_vector(const vec3& v) {
    return v / length(v);
}

using point3 = vec3;  // 3D point
using color  = vec3;  // RGB color



#endif 