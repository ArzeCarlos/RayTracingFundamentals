#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera{
    public:
        camera(double aspect_ratio = 16.0 / 9.0, int image_width=400){
            this->aspect_ratio = aspect_ratio;
            this->image_width = image_width;
            image_height = std::max(1, int(image_width / aspect_ratio));

            auto viewport_height = 2.0;
            auto viewport_width  = viewport_height * aspect_ratio;
            auto focal_length = 1.0;

            origin = point3(0,0,0);
            horizontal = vec3(viewport_width, 0, 0);
            vertical   = vec3(0, viewport_height, 0);
            lower_left = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);

        }
        int width()const { return image_width;}
        int height()const { return image_height;}
        ray get_ray(double u, double v) const {
            return ray(origin, lower_left + u*horizontal + v*vertical - origin);
        }


    private:
        double aspect_ratio;
        int image_width;
        int image_height;

        point3 origin;
        vec3 horizontal;
        vec3 vertical;
        point3 lower_left;
};

#endif