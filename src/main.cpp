#include <fstream>
#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, double radius, const ray& r, double& t_hit) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto disc = half_b*half_b - a*c;
    if (disc < 0) return false;
    t_hit = (-half_b - std::sqrt(disc)) / a;
    if (t_hit <= 0) {
        t_hit = (-half_b + std::sqrt(disc)) / a;
        if (t_hit <= 0) return false;
    }
    return true;
}


color ray_color(const ray& r) {
    double t;
    point3 center(0,0,-1);
    double radius = 0.5;
    if (hit_sphere(center, radius, r, t)) {
        point3 p = r.at(t);
        vec3 N = unit_vector(p - center);
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_dir = unit_vector(r.direction());
    double k = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - k)*color(1,1,1) + k*color(0.5,0.7,1.0);
}

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width     = 400;
    const int image_height    = static_cast<int>(image_width / aspect_ratio);

    std::ofstream out("out/image.ppm");
    if (!out) { std::cerr << "Failed to open output file.\n"; return 1; }
    out << "P3\n" << image_width << " " << image_height << "\n255\n";

    // Camera (simple pinhole, no class yet)
    double viewport_height = 2.0;
    double viewport_width  = aspect_ratio * viewport_height;
    double focal_length    = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    point3 lower_left_corner =
        origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            double u = double(i) / (image_width  - 1);
            double v = double(j) / (image_height - 1);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(out, pixel_color);
        }
    }
    std::cerr << "\nDone.                 \n";
    return 0;
}