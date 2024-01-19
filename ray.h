#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
 public:

  //Declare some constructors for rays
  ray() {}

  ray(const point3& origin, const vec3& direction) {
    orig = origin;
    dir = direction;
  }

  // Retrieve a rays value
  point3 origin() const {return orig;}
  vec3 direction() const {return dir; }

  // Retrieve the point at length t
  point3 at(double t) const {
    return orig + t*dir;
  }

 private:
  point3 orig;
  vec3 dir;
};

#endif
