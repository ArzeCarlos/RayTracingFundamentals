#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <algorithm>
#include "vec3.h"

/**
 * @brief Writes a color to an output stream
 * 
 * @details Converts RGB component of a color [0.0, 1.0] to [0, 255]
 * and writes the result in the provided output stream. Gamma-correct
 */

inline void write_color(std::ostream& out, const color& pixel_color, int samples_per_pixel) {
    
    const double scale = 1.0 / samples_per_pixel;

    double r = std::sqrt(pixel_color.x() * scale);
    double g = std::sqrt(pixel_color.y() * scale);
    double b = std::sqrt(pixel_color.z() * scale);

    r = std::clamp(r, 0.0, 0.999);
    g = std::clamp(g, 0.0, 0.999);
    b = std::clamp(b, 0.0, 0.999);

    out << static_cast<int>(256 * r) << ' '
        << static_cast<int>(256 * g) << ' '
        << static_cast<int>(256 * b) << '\n';
}

#endif 