#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include "ray.h"
#include "vec3.h"
#include "random_utils.h"

struct hit_record;

class material {
public:
    virtual ~material() = default;
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
    lambertian(const color& a) : albedo(a) {}

    bool scatter(const ray&, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 scatter_dir = rec.normal + random_unit_vector();
        if (scatter_dir.length_squared() < 1e-12) scatter_dir = rec.normal;
        scattered = ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif 