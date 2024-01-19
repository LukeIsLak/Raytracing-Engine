#ifndef HITTABLE_H
#define HITTABLE_H


class material;

class hit_record {
 public:
  point3 p;
  vec3 normal;
  shared_ptr<material> mat;
  double t;
  bool front_face;

  //Detect if the ray hit inside an object or not
  void set_face_normal(const ray& r, const vec3& o_normal) {
    front_face = dot(r.direction(), o_normal) < 0;
    normal = front_face ? o_normal : -o_normal;
  }
};

class hittable {
 public:
  virtual ~hittable() = default;

  // for something to be hittable it needs to contain this
  virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
