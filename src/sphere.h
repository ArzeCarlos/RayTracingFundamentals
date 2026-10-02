#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "hittable.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto half_b = dot(oc, r.direction());
        auto c = dot(oc, oc) - radius*radius;
        auto disc = half_b*half_b - a*c;
        if (disc < 0) return false;
        auto sqrtd = std::sqrt(disc);

        auto root = (-half_b - sqrtd)/a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd)/a;
            if (root < t_min || t_max < root) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        return true;
    }

private:
    point3 center;
    double radius;
};

#endif // SPHERE_H