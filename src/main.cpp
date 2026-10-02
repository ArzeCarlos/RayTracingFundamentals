#include <fstream>
#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0.001, 1e30, rec))
        return 0.5 * (rec.normal + color(1,1,1));

    vec3 unit_dir = unit_vector(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1.0);
}

int main() {
    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100.0));

    // Camera
    camera cam(16.0/9.0, 400);
    const int image_width = cam.width();
    const int image_height = cam.height();

    std::ofstream out("out/image.ppm");
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width-1);
            double v = double(j) / (image_height-1);
            ray r = cam.get_ray(u, v);
            write_color(out, ray_color(r, world));
        }
    }
    std::cerr << "\nDone.                 \n";
}