#include <fstream>
#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

color ray_color(const ray& r, const hittable& world, int depth) {
    if (depth <= 0) return color(0,0,0);

    hit_record rec;
    if (world.hit(r, 0.001, 1e30, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat && rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return color(0,0,0);
    }
    vec3 unit_dir = unit_vector(r.direction());
    double t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1.0);
}


int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 10;

    std::ofstream out("out/image.ppm");
    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Materials
    auto mat_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto mat_center = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));

    // World
    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100.0, mat_ground));
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5, mat_center));

    // Camera
    camera cam(aspect_ratio, image_width);

    // Render
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(out, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.                 \n";
}