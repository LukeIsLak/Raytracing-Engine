#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
  public:
 sphere(point3 _center, double _radius, shared_ptr<material> _material) : center(_center), radius(_radius), mat(_material) {}

  //Checks if a ray has hit a given sphere
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

      // With a given vector, we know if a vector is inside a sphere if the given sphere that the vector orresponds to is inside the original sphere
      // That is, with the formala x^2 + y^2 + z^2 = r^2, a point is inside the sphere if x^2 + y^2 + z^2 < r^2
      // Where x, y, and z is the vector minus the center (an abritrary point)

      // Given a ray of formala mx + b, subsitutes into the vector, we can solve for x using the quadratic formula
      // This says that if we have at least one root, we have hit the sphere, such we want to colour it
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
	
	//If the root is not in the range of the interval, return false
        if (!ray_t.surround(root)) {
            root = (-half_b + sqrtd) / a;
            if (!ray_t.surround(root))
                return false;
        }

	// Add to the hit record the root, essentially log that the ray hit something with distance root, at length (where it hit) 
        rec.t = root;
        rec.p = r.at(rec.t);

	// Define the normal vector of what we hit, will be useful later
        rec.set_face_normal(r, (rec.p - center) / radius);
	rec.mat = mat;

        return true;
    }

  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
};

#endif
