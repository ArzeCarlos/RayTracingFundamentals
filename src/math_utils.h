#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "vec3.h"

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v, n)*n;
}

#endif 
