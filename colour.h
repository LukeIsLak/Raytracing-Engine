#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include <iostream>

using colour = vec3;

inline double linear_to_gamma (double t) {
  return sqrt(t);
}

inline void return_colour (std::ostream &out, colour pixel_colour, int samples_per_pixel) {
  //Translate the vec3 into a colour pixel [0,255], output it to the current stream

  auto r = pixel_colour.x();
  auto g = pixel_colour.y();
  auto b = pixel_colour.z();

  auto scale = 1.0 / samples_per_pixel;

  r = linear_to_gamma(r * scale);
  g = linear_to_gamma(g * scale);
  b = linear_to_gamma(b * scale);

  static const interval intensity(0.000, 0.999);

  auto out_r = static_cast<int>(256 * intensity.clamp(r));
  auto out_g = static_cast<int>(256 * intensity.clamp(g));
  auto out_b = static_cast<int>(256 * intensity.clamp(b));

  out << out_r << ' ' << out_g << ' ' << out_b << '\n';
}

#endif