#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

//Easily have a list of objects
using std::shared_ptr;
using std::make_shared;


//A class to define a list of objects we wish to render
class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

	// For each bject in the world
        for (const auto& object : objects) {
	  
	  // Cast a ray to it, detect if it is hit within the interval from the camera to the previous hit object
	  // If it is within the interval, change the hit object to the new, closer object
	  if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;

		//Modify the hit record to the new one
                rec = temp_rec;
            }
        }
	
	// Return if something was hit
        return hit_anything;
    }
};

#endif