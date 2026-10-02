#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include <cmath>
#include "hittable.h"
#include "material.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere(point3 cen, double r, std::shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(std::move(m)) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto half_b = dot(oc, r.direction());
        auto c = dot(oc, oc) - radius*radius;
        auto disc = half_b*half_b - a*c;
        if (disc < 0) return false;
        auto sqrtd = std::sqrt(disc);

        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = mat_ptr;
        return true;
    }

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;
};

#endif // SPHERE_H