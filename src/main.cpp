#include <iostream>
#include <memory>

#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "camera.h"

int main() {
    hittable_list world;

    auto ground = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    auto glass = std::make_shared<dielectric>(1.5);
    auto metal1 = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
    auto red = std::make_shared<lambertian>(color(0.8, 0.2, 0.2));

    world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000.0, ground));
    world.add(std::make_shared<sphere>(point3(-1, 0, -1), 0.5, glass));
    world.add(std::make_shared<sphere>(point3(1, 0, -1), 0.5, metal1));
    world.add(std::make_shared<sphere>(point3(0, 0, -1.6), 0.5, red));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.lookfrom = point3(3, 3, 2);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1, 0);
    cam.vfov = 20.0;

    cam.focus_dist =(cam.lookfrom - cam.lookat).length();

    cam.defocus_angle = 3.0;
    cam.render(world);

    return 0;
}
