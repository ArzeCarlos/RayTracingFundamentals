#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <algorithm>
#include "vec3.h"

/**
 * @brief Writes a color to an output stream
 * 
 * @details Converts RGB component of a color [0.0, 1.0] to [0, 255]
 * and writes the result in the provided output stream.
 */

inline void write_color(std::ostream& out, const color& pixel_color){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = std::clamp(r, 0.0, 0.999);
    g = std::clamp(g, 0.0, 0.999);
    b = std::clamp(b, 0.0, 0.999);

    out << static_cast<int>(256*r) << ' '
        << static_cast<int>(256*g) << ' ' 
        << static_cast<int>(256*b) << '\n'; 
}


#endif COLOR_H