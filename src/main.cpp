#include <iostream>
#include <memory>
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "camera.h"

int main() {
    // World: ground + three spheres with simple materials
    hittable_list world;
    auto ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto red    = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto metal1 = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.1);

    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100.0, ground));
    world.add(std::make_shared<sphere>(point3(0,0,-1),     0.5,  red));
    world.add(std::make_shared<sphere>(point3(-1,0,-1),    0.5,  metal1));

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 50;
    cam.max_depth = 10;
    cam.lookfrom = point3(3,3,2);
    cam.lookat   = point3(0,0,-1);
    cam.vfov     = 20.0;

    cam.render(world);
}