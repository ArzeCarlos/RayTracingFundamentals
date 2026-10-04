#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "vec3.h"
#include "constants.h"

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v, n)*n;
}

inline double schlick_reflectance(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0*r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}

inline vec3 refract(const vec3& uv, const vec3& n, double eta_over_eta_prime) {
    double cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = eta_over_eta_prime * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}



#endif 
