#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "hittable.h"

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list() {}
    explicit hittable_list(std::shared_ptr<hittable> obj) { add(obj); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> obj) { objects.push_back(obj); }

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        hit_record temp;
        bool hit_anything = false;
        auto closest = t_max;

        for (const auto& obj : objects) {
            if (obj->hit(r, t_min, closest, temp)) {
                hit_anything = true;
                closest = temp.t;
                rec = temp;
            }
        }
        return hit_anything;
    }
};

#endif // HITTABLE_LIST_H